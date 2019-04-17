//
// Created by 민지우 on 2019-04-13.
//

#ifndef EMBEDED_TIMER_H
#define EMBEDED_TIMER_H

void timer_start (time_t tid, void(*func)(int), long nsec_interval);
void timer_cancel ();

#endif //EMBEDED_TIMER_H
