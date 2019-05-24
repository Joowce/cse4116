//
// Created by 민지우 on 2019-05-23.
//

#ifndef EMBEDED_TIMER_H
#define EMBEDED_TIMER_H

void init_stopwatch (void(*after_handler)(unsigned long));
void stopwatch_pause ();
void start_stopwatch (void(*blink_handler)(unsigned long));

#endif //EMBEDED_TIMER_H
