//
// Created by 민지우 on 2019-05-23.
//

#include <linux/timer.h>
#include <asm/div64.h>
#include "timer.h"

#define NO_LAP 0

/**
 * stopwatch structure
 * timer_list: for timer
 * start: stopwatch start time
 * rest: store rest of expires, when stopwatch stop
 * blink_handler: handler that is called when stopwatch blink
 */
struct Stopwatch {
    struct timer_list timer;
    unsigned long duration;
    unsigned long rest_clocks;
    TimerStatus status;
    void (*blink_handler) (unsigned long);
};

static struct Stopwatch stopwatch;
/**
 * set timer after clocks, and set func
 * @param clocks : duration clocks
 * @param func : callback function
 */
static void set_timeout (long clocks, void (*func) (unsigned long)) {
    stopwatch.timer.expires = get_jiffies_64() + (clocks);
    stopwatch.timer.data = (unsigned long)&stopwatch;
    stopwatch.timer.function = func;

    add_timer(&stopwatch.timer);
}

/**
 * call timer.func, and set timer
 * @param timeout : duration
 */
static void stopwatch_blink (unsigned long timeout) {
    struct Stopwatch *p_watch = (struct Stopwatch*) timeout;

    unsigned long duration = p_watch -> duration = p_watch -> duration + 1;
    p_watch->blink_handler(duration);

    set_timeout(HZ, stopwatch_blink);
    printk(KERN_INFO "[stopwatch blink] sec: %ld", duration);
}

/**
 * initialize stopwatch data
 * timer initialized
 * @param after_handler : called after initialization
 */
void stopwatch_init (void(*after_handler)(unsigned long)) {
    stopwatch.status = TIMER_INIT;
    stopwatch.duration = 0;
    stopwatch.rest_clocks = NO_LAP;

    init_timer(&(stopwatch.timer));
    after_handler(0);
}

/**
 * stop stopwatch
 * delete timer and store rest of expire clocks
 */
void stopwatch_pause () {
    stopwatch.rest_clocks = stopwatch.timer.expires - get_jiffies_64();
    stopwatch.status = TIMER_PAUSE;
    del_timer_sync(&(stopwatch.timer));
    printk("[stopwatch pause] rest clocks: %ld", stopwatch.rest_clocks);
}

/**
 * start stopwatch
 * if previous status is pause, set expires to rest clocks
 * @param blink_handler : executed when blink
 */
void stopwatch_start (void(*blink_handler)(unsigned long)) {
    unsigned long prev_status = stopwatch.status;

    if(blink_handler != NULL) stopwatch.blink_handler = blink_handler;
    stopwatch.status = TIMER_RUNNING;
    set_timeout(prev_status == TIMER_PAUSE ? stopwatch.rest_clocks : HZ, stopwatch_blink);

    if (prev_status == TIMER_PAUSE) stopwatch.rest_clocks = NO_LAP;
}

/**
 * pause stopwatch
 * initialize stopwatch data
 * @param after_handler : called after reset
 */
void stopwatch_reset (void(*after_handler)(unsigned long)) {
    stopwatch_pause();
    stopwatch_init(after_handler);
}


/**
 * get timer status
 * @return TimerStatus: timer status
 */
TimerStatus stopwatch_get_status () {
    return stopwatch.status;
}
