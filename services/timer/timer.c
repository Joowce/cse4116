//
// Created by 민지우 on 2019-04-13.
//

#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#include "timer.h"
#include "../log/log.h"

struct itimerval set_time_val;

void timer_start (time_t tid, void(*func)(int), long nsec_interval) {

    sigset(SIGALRM, func);

    set_time_val.it_value.tv_sec = nsec_interval;
    set_time_val.it_value.tv_usec = 0;

    set_time_val.it_interval.tv_sec = nsec_interval;
    set_time_val.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL, &set_time_val, NULL);
    LOG_INFO("TIMER:: start timer");
}

void timer_cancel () {
    struct itimerval get_time_val;

    if (getitimer(ITIMER_REAL, &get_time_val) == -1) {
        LOG_ERROR("TIMER:: can not get timer");
        return;
    }

    signal(SIGALRM, SIG_IGN);
    LOG_INFO("TIMER:: timer value [%d]", get_time_val.it_value.tv_sec);
}