//
// Created by 민지우 on 2019-05-24.
//
#include <asm/div64.h>
#include <linux/kernel.h>

#include "stopwatch_controller.h"
#include "timer.h"
#include "device.h"

static void write_duration (unsigned long);

/**
 * stopwatch start
 * if timer is running, then pass
 */
void stopwatch_ctrl_start() {
    if(stopwatch_get_status() == TIMER_RUNNING) return;

    stopwatch_start(write_duration);
    printk(KERN_INFO "[stopwatch ctrl start] start\n");
}

/**
 * stopwatch pause
 * if stopwatch is running, then pause
 * if stopwatch is paused, then running
 */
void stopwatch_ctrl_pause() {
    if (stopwatch_get_status() == TIMER_RUNNING) {
        stopwatch_pause();
        printk(KERN_INFO "[stopwatch ctrl pause] pause\n");
    }
    else {
        stopwatch_start(write_duration);
        printk(KERN_INFO "[stopwatch ctrl pause] start\n");
    }
}

/**
 * stopwatch reset
 * reset stopwatch data
 * if stopwatch was running, start stopwatch
 */
void stopwatch_ctrl_reset() {
    TimerStatus status = stopwatch_get_status();
    stopwatch_reset(write_duration);
    
    if (status == TIMER_RUNNING) {
        stopwatch_start(write_duration);
        printk(KERN_INFO "[stopwatch ctrl reset] reset running\n");
    } else printk(KERN_INFO "[stopwatch ctrl reset] reset only data\n");
}

/**
 * stopwatch exit
 * reset stopwatch data
 */
void stopwatch_ctrl_exit() {
    stopwatch_reset(write_duration);
    printk(KERN_INFO "[stopwatch ctrl exit] exit\n");
}

/**
 * stopwatch initialize
 * 1. initialize fnd device
 * 2. initialize stopwatch data
 */
void stopwatch_ctrl_init() {
    fnd_init();
    stopwatch_init(write_duration);
    printk(KERN_INFO "[stopwatch ctrl init] init\n");
}

/**
 * write duration time to fnd device
 * result array has fnd values
 * @param duration: seconds
 */
static void write_duration (unsigned long duration) {
    int min = do_div(duration, 60), sec = duration % 60;
    char result[4];

    result[0] = do_div(min, 10);
    result[1] = min % 10;
    result[2] = do_div(sec, 10);
    result[3] = sec % 10;

    fnd_write(result);
    printk(KERN_INFO "[write duration] min: %d sec %d\n", min, sec);
}
