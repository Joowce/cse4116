//
// Created by 민지우 on 2019-05-23.
//

#include <linux/timer.h>
#include "timer.h"

#define NO_LAP -1

/**
 * stopwatch structure
 * timer_list: for timer
 * start: stopwatch start time
 * rest: store rest of expires, when stopwatch stop
 * blink_handler: handler that is called when stopwatch blink
 */
static struct Stopwatch {
    struct timer_list timer;
    unsigned long start;
    unsigned long rest;
    void (*blink_handler) (unsigned long);
};

struct Stopwatch stopwatch;

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

    unsigned long time = get_jiffies_64() - p_watch -> start;
    p_watch->blink_handler(time);

    set_timeout(HZ, stopwatch_blink);
}

/**
 * initialize stopwatch data
 * @param after_handler : called after initialization
 */
void init_stopwatch (void(*after_handler)(unsigned long)) {

    stopwatch.start = get_jiffies_64();
    stopwatch.blink_handler = blink_handler;
    stopwatch.rest = NO_LAP;

    after_handler(get_jiffies_64() - stopwatch.start);
}

/**
 * stop stopwatch
 * delete timer and store rest of expire clocks
 */
void stopwatch_pause () {
    stopwatch.rest = stopwatch.timer.expires - get_jiffies_64();
    del_timer_sync(&(stopwatch.timer));
}

/**
 * start stopwatch
 * if lap is existed, set expires to rest
 * @param blink_handler : executed when blink
 */
void start_stopwatch (void(*blink_handler)(unsigned long)) {
    unsigned long rest = stopwatch.rest;

    set_timeout(rest == NO_LAP ? HZ : stopwatch.rest, blink_handler);

    if (rest != NO_LAP) stopwatch.rest = NO_LAP;
}

TimerStatus get_stopwatch_status () {
    return stopwatch.rest == NO_LAP ? TIMER_RUNNING : TIMER_PAUSE;
}