//
// Created by 민지우 on 2019-05-24.
//
#include "stopwatch_controller.h"
#include "timer.h"
#include "device.h"

static void write_duration (unsigned long);
void stopwatch_ctrl_start() {
    if(stopwatch_get_status() == TIMER_RUNNING) return IRQ_HANDLED;

    stopwatch_start(write_duration);
}

void stopwatch_ctrl_pause() {
    if (stopwatch_get_status() == TIMER_RUNNING) stopwatch_pause();
    else stopwatch_start(write_duration);

}

void stopwatch_ctrl_reset() {
    TimerStatus status = stopwatch_get_status();
    stopwatch_reset(write_duration);
    
    if (status == TIMER_RUNNING) stopwatch_start(write_duration);
}

void stopwatch_ctrl_exit() {
    stopwatch_reset(write_duration);
}

void stopwatch_ctrl_init() {
    stopwatch_init(write_duration);
}

static void write_duration (unsigned long duration) {
    int min = duration / 60, sec = duration % 60;
    char[4] result;

    result[0] = min / 10;
    result[1] = min % 10;
    result[2] = sec / 10;
    result[3] = sec % 10;

    fnd_write(result);
}