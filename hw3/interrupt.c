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

#define STOPWATCH_MAJOR 242
#define STOPWATCH_MINOR 0
#define STOPWATCH_NAME "stopwatch"

static int inter_open(struct inode *, struct file *);
static int inter_release(struct inode *, struct file *);
static int inter_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos);

irqreturn_t inter_handler1(int irq, void* dev_id, struct pt_regs* reg);
irqreturn_t inter_handler2(int irq, void* dev_id, struct pt_regs* reg);
irqreturn_t inter_handler3(int irq, void* dev_id, struct pt_regs* reg);
irqreturn_t inter_handler4(int irq, void* dev_id, struct pt_regs* reg);

static inter_usage=0;
int interruptCount=0;

static struct file_operations inter_fops =
{
	.open = inter_open,
	.write = inter_write,
	.release = inter_release,
};

irqreturn_t inter_handler1(int irq, void* dev_id, struct pt_regs* reg) {
	printk(KERN_ALERT "interrupt1!!! = %x\n", gpio_get_value(IMX_GPIO_NR(1, 11)));
	return IRQ_HANDLED;
}

irqreturn_t inter_handler2(int irq, void* dev_id, struct pt_regs* reg) {
        printk(KERN_ALERT "interrupt2!!! = %x\n", gpio_get_value(IMX_GPIO_NR(1, 12)));
        return IRQ_HANDLED;
}

irqreturn_t inter_handler3(int irq, void* dev_id,struct pt_regs* reg) {
        printk(KERN_ALERT "interrupt3!!! = %x\n", gpio_get_value(IMX_GPIO_NR(2, 15)));
        return IRQ_HANDLED;
}

irqreturn_t inter_handler4(int irq, void* dev_id, struct pt_regs* reg) {
        printk(KERN_ALERT "interrupt4!!! = %x\n", gpio_get_value(IMX_GPIO_NR(5, 14)));
        return IRQ_HANDLED;
}


static int inter_open(struct inode *minode, struct file *mfile){
	int ret;
	int irq;

	printk(KERN_ALERT "Open Module\n");

	// int1
	gpio_direction_input(IMX_GPIO_NR(1,11));
	irq = gpio_to_irq(IMX_GPIO_NR(1,11));
	printk(KERN_ALERT "IRQ Number : %d\n",irq);
	//ret=request_irq();

	// int2
	gpio_direction_input(IMX_GPIO_NR(1,12));
	irq = gpio_to_irq(IMX_GPIO_NR(1,12));
	printk(KERN_ALERT "IRQ Number : %d\n",irq);
	//ret=request_irq();

	// int3
	gpio_direction_input(IMX_GPIO_NR(2,15));
	irq = gpio_to_irq(IMX_GPIO_NR(2,15));
	printk(KERN_ALERT "IRQ Number : %d\n",irq);
	//ret=request_irq();

	// int4
	gpio_direction_input(IMX_GPIO_NR(5,14));
	irq = gpio_to_irq(IMX_GPIO_NR(5,14));
	printk(KERN_ALERT "IRQ Number : %d\n",irq);
	//ret=request_irq();

	return 0;
}

static int inter_release(struct inode *minode, struct file *mfile){
	free_irq(gpio_to_irq(IMX_GPIO_NR(1, 11)), NULL);
	free_irq(gpio_to_irq(IMX_GPIO_NR(1, 12)), NULL);
	free_irq(gpio_to_irq(IMX_GPIO_NR(2, 15)), NULL);
	free_irq(gpio_to_irq(IMX_GPIO_NR(5, 14)), NULL);
	
	printk(KERN_ALERT "Release Module\n");
	return 0;
}

static int inter_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos ){
	printk("write\n");
	return 0;
}

static int __init inter_init(void) {
	int result;
	if((result = register_chrdev(STOPWATCH_MAJOR, STOPWATCH_NAME, &inter_fops)) < 0 )
		return result;
	printk(KERN_ALERT "Init Module Success \n");
	printk(KERN_ALERT "Device : /dev/%s, Major Num : %d \n", STOPWATCH_NAME, STOPWATCH_MAJOR);
	return 0;
}

static void __exit inter_exit(void) {
	unregister_chrdev(STOPWATCH_MAJOR, STOPWATCH_NAME);
	printk(KERN_ALERT "Remove Module Success \n");
}

module_init(inter_init);
module_exit(inter_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR ("author");