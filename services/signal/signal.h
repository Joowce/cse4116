//
// Created by 민지우 on 2019-04-10.
//

#ifndef EMBEDED_SIGNAL_H
#define EMBEDED_SIGNAL_H
#include <signal.h>

struct sigaction create_signal_action(int signo, void (*handler) (int), const sigset_t* sa_mask);
void send_signal (pid_t pid, int sig);
void ignore_signal (int);

#endif //EMBEDED_SIGNAL_H
