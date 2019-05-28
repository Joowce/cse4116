//
// Created by 민지우 on 2019-05-23.
//

#ifndef EMBEDED_TIMER_H
#define EMBEDED_TIMER_H

typedef enum _TimerStatus {TIMER_PAUSE, TIMER_RUNNING} TimerStatus;

void stopwatch_init (void(*after_handler)(unsigned long));
void stopwatch_pause ();
void stopwatch_start (void(*blink_handler)(unsigned long));
TimerStatus stopwatch_get_status ()

#endif //EMBEDED_TIMER_H
