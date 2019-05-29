#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <asm/irq.h>
#include <mach/gpio.h>
#include <linux/platform_device.h>
#include <asm/gpio.h>
#include <linux/wait.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/ioport.h>
#include <linux/version.h>
#include <linux/cdev.h>

#include "stopwatch_controller.h"

#define STOPWATCH_MAJOR 242
#define STOPWATCH_MINOR 0
#define STOPWATCH_NAME "stopwatch"

DECLARE_WAIT_QUEUE_HEAD(wait_queue);

static int inter_open(struct inode *, struct file *);
static int inter_release(struct inode *, struct file *);
static int inter_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos);

irqreturn_t handler_home(int irq, void* dev_id, struct pt_regs* reg);
irqreturn_t handler_back(int irq, void* dev_id, struct pt_regs* reg);
irqreturn_t handler_vol_up(int irq, void* dev_id, struct pt_regs* reg);
irqreturn_t handler_vol_down_falling(int irq, void* dev_id, struct pt_regs* reg);
irqreturn_t handler_vol_down_rising(int irq, void* dev_id, struct pt_regs* reg);

static unsigned long vol_down_pressed_start_time = -1;
/**
 * for vol- button
 * save start time for pressing
 * check user pressing during 3 sec
 */
static unsigned long vol_down_pressed_start_time = NULL;

/**
 * module's file operations
 */
static struct file_operations inter_fops =
{
	.open = inter_open,
	.write = inter_write,
	.release = inter_release,
};

/**
 * home button handler
 * stopwatch start
 * @param irq
 * @param dev_id
 * @param reg
 * @return
 */
irqreturn_t handler_home(int irq, void* dev_id, struct pt_regs* reg) {
	printk(KERN_ALERT "home interrupt\n");
    stopwatch_ctrl_start();
	return IRQ_HANDLED;
}

/**
 * back button handler
 * stopwatch pause
 * @param irq
 * @param dev_id
 * @param reg
 * @return
 */
irqreturn_t handler_back(int irq, void* dev_id, struct pt_regs* reg) {
        printk(KERN_ALERT "back interrupt\n");
        stopwatch_ctrl_pause();
        return IRQ_HANDLED;
}

/**
 * vol+ handler
 * stopwatch reset
 * @param irq
 * @param dev_id
 * @param reg
 * @return
 */
irqreturn_t handler_vol_up(int irq, void* dev_id,struct pt_regs* reg) {
        printk(KERN_ALERT "vol up interrupt\n");
        stopwatch_ctrl_reset();
        return IRQ_HANDLED;
}

/**
 * vol- falling handler
 * if start_time is -1, set start_time
 * if handler called after 3 seconds, then stopwatch exit and wake_up wait_queue
 * @param irq
 * @param dev_id
 * @param reg
 * @return
 */
irqreturn_t handler_vol_down_falling(int irq, void* dev_id, struct pt_regs* reg) {
        printk(KERN_ALERT "vol down interrupt\n");

        if (vol_down_pressed_start_time == -1) {
            vol_down_pressed_start_time = get_jiffies_64();
        } else if (get_jiffies_64() - vol_down_pressed_start_time >= 3 * HZ) {
            stopwatch_ctrl_exit();
            vol_down_pressed_start_time = -1;
            __wake_up(&wait_queue, 1, 1, NULL);
        }

        return IRQ_HANDLED;
}

/**
 * vol- rising handler
 * unset start_time
 * @param irq
 * @param dev_id
 * @param reg
 * @return
 */
irqreturn_t handler_vol_down_rising (int irq, void* dev_id, struct pt_regs* reg) {
        printk(KERN_ALERT "vol down interrupt\n");
        vol_down_pressed_start_time = -1;
	return IRQ_HANDLED;
}


/**
 * interrupt open
 * connected with fops.open
 * register interrupt handlers
 * unset start time
 * @param minode
 * @param mfile
 * @return
 */
static int inter_open(struct inode *minode, struct file *mfile){
	irqreturn_t ret;
	int irq;

	printk(KERN_ALERT "Open Module\n");

	gpio_direction_input(IMX_GPIO_NR(1,11));
	irq = gpio_to_irq(IMX_GPIO_NR(1,11));
	printk(KERN_ALERT "IRQ Number : %d\n",irq);
	ret=request_irq(irq, handler_home, IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING, "home", 0);

	gpio_direction_input(IMX_GPIO_NR(1,12));
	irq = gpio_to_irq(IMX_GPIO_NR(1,12));
	printk(KERN_ALERT "IRQ Number : %d\n",irq);
    ret=request_irq(irq, handler_back, IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING, "back", 0);

	gpio_direction_input(IMX_GPIO_NR(2,15));
	irq = gpio_to_irq(IMX_GPIO_NR(2,15));
	printk(KERN_ALERT "IRQ Number : %d\n",irq);
    ret=request_irq(irq, handler_vol_up, IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING, "vol_up", 0);

	// int4
	gpio_direction_input(IMX_GPIO_NR(5,14));
	irq = gpio_to_irq(IMX_GPIO_NR(5,14));
	printk(KERN_ALERT "IRQ Number : %d\n",irq);
    ret=request_irq(irq, handler_vol_down_falling, IRQF_TRIGGER_FALLING, "vol_down_falling", 0);
    ret=request_irq(irq, handler_vol_down_rising, IRQF_TRIGGER_RISING, "vol_down_rising", 0);


	vol_down_pressed_start_time = -1;
	return 0;
}

/**
 * interrupt release
 * connected with fops.release
 * free interrupt handler
 * unset start time
 * @param minode
 * @param mfile
 * @return
 */
static int inter_release(struct inode *minode, struct file *mfile){
	free_irq(gpio_to_irq(IMX_GPIO_NR(1, 11)), NULL);
	free_irq(gpio_to_irq(IMX_GPIO_NR(1, 12)), NULL);
	free_irq(gpio_to_irq(IMX_GPIO_NR(2, 15)), NULL);
	free_irq(gpio_to_irq(IMX_GPIO_NR(5, 14)), NULL);

	vol_down_pressed_start_time = -1;
	printk(KERN_ALERT "Release Module\n");
	return 0;
}

/**
 * interrupt write
 * connected with fops.write
 * @param filp
 * @param buf
 * @param count
 * @param f_pos
 * @return
 */
static int inter_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos ){
	interruptible_sleep_on(&wait_queue);
	printk("write\n");
	return 0;
}

/**
 * inter initialize
 * for module initialize
 * register inter_fops
 */
static int __init inter_init(void) {
	int result;
	if((result = register_chrdev(STOPWATCH_MAJOR, STOPWATCH_NAME, &inter_fops)) < 0 )
		return result;
	printk(KERN_ALERT "Init Module Success \n");
	printk(KERN_ALERT "Device : /dev/%s, Major Num : %d \n", STOPWATCH_NAME, STOPWATCH_MAJOR);
	return 0;
}

/**
 * inter exit
 * for module exit
 * unregister this module
 */
static void __exit inter_exit(void) {
	unregister_chrdev(STOPWATCH_MAJOR, STOPWATCH_NAME);
	printk(KERN_ALERT "Remove Module Success \n");
}

module_init(inter_init);
module_exit(inter_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR ("author");
