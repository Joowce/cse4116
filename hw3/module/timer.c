//
// Created by 민지우 on 2019-05-23.
//

#include <linux/timer.h>
#include <asm/div64.h>
#include "timer.h"

#define NO_LAP -1

/**
 * stopwatch structure
 * timer_list: for timer
 * start: stopwatch start time
 * rest: store rest of expires, when stopwatch stop
 * blink_handler: handler that is called when stopwatch blink
 */
struct Stopwatch {
    struct timer_list timer;
    unsigned long start;
    unsigned long rest;
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

    unsigned long diff = get_jiffies_64() - (p_watch -> start);
    unsigned long sec = do_div(diff, HZ);
    p_watch->blink_handler(sec);

    set_timeout(HZ, stopwatch_blink);
    printk(KERN_INFO "[stopwatch blink] sec: %ld", sec);
}

/**
 * initialize stopwatch data
 * timer initialized
 * @param after_handler : called after initialization
 */
void stopwatch_init (void(*after_handler)(unsigned long)) {
    stopwatch.status = TIMER_PAUSE;
    stopwatch.start = get_jiffies_64();
    stopwatch.rest = NO_LAP;

    init_timer(&(stopwatch.timer));
    after_handler(0);
}

/**
 * stop stopwatch
 * delete timer and store rest of expire clocks
 */
void stopwatch_pause () {
    stopwatch.rest = stopwatch.timer.expires - get_jiffies_64();
    stopwatch.status = TIMER_PAUSE;
    del_timer_sync(&(stopwatch.timer));
}

/**
 * start stopwatch
 * if lap is existed, set expires to rest
 * @param blink_handler : executed when blink
 */
void stopwatch_start (void(*blink_handler)(unsigned long)) {
    unsigned long rest = stopwatch.rest;

    if(blink_handler != NULL) stopwatch.blink_handler = blink_handler;
    if (rest == NO_LAP) stopwatch.start = get_jiffies_64();
    stopwatch.status = TIMER_RUNNING;
    set_timeout(rest == NO_LAP ? HZ : stopwatch.rest, stopwatch_blink);

    if (rest != NO_LAP) stopwatch.rest = NO_LAP;
}

/**
 * pause stopwatch
 * reset stopwatch data
 * @param after_handler : called after reset
 */
void stopwatch_reset (void(*after_handler)(unsigned long)) {
    stopwatch_pause();
    stopwatch.start = get_jiffies_64();
    stopwatch.rest = NO_LAP;

    after_handler(0);
}


/**
 * get timer status
 * @return TimerStatus: timer status
 */
TimerStatus stopwatch_get_status () {
    return stopwatch.status;
}
