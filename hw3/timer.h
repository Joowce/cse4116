//
// Created by 민지우 on 2019-05-23.
//

#ifndef EMBEDED_TIMER_H
#define EMBEDED_TIMER_H

typedef enum _TimerStatus {TIMER_PAUSE, TIMER_RUNNING} TimerStatus;

void init_stopwatch (void(*after_handler)(unsigned long));
void stopwatch_pause ();
void start_stopwatch (void(*blink_handler)(unsigned long));
TimerStatus get_stopwatch_status ()

#endif //EMBEDED_TIMER_H
