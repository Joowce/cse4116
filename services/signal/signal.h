//
// Created by 민지우 on 2019-04-10.
//

#ifndef EMBEDED_SIGNAL_H
#define EMBEDED_SIGNAL_H
#include <signal.h>

struct sigaction create_signal(int signo, void (*handler) (int), const sigset_t* sa_mask);

#endif //EMBEDED_SIGNAL_H
