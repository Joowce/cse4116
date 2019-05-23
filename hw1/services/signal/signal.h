//
// Created by 민지우 on 2019-04-10.
//

#include <signal.h>

#ifndef EMBEDED_SIGNAL_H
#define EMBEDED_SIGNAL_H

int reg_signal_handler(int signo, void (*handler) (int));
void send_signal (pid_t pid, int sig);
void ignore_signal (int);

#endif //EMBEDED_SIGNAL_H
