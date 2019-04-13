//
// Created by 민지우 on 2019-04-13.
//

#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#include "timer.h"

void start_timer (void(*func)(int), long nsec_interval) {
    struct itimerval timer;
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = func;
    sigaction(SIGVTALRM, &sa, NULL);

    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = nsec_interval;

    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = nsec_interval;

    setitimer(ITIMER_VIRTUAL, &timer, NULL);
}
