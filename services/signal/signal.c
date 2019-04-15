//
// Created by 민지우 on 2019-04-10.
//

#include <stdio.h>

#include "signal.h"
#include "../log/log.h"

struct sigaction create_signal_action(int signo, void (*handler) (int), const sigset_t* sa_mask) {
    struct sigaction act;
    act.sa_handler = handler;

    if (sa_mask != NULL) act.sa_mask = *sa_mask;
    sigaction(signo, &act, NULL);

    return act;
}

void send_signal (pid_t pid, int sig) {
    kill(pid, sig);
    LOG_INFO("signal:: send [%d] signal to [%d] process", sig, pid);
}

void ignore_signal (int sig) {
    signal(sig, SIG_IGN);
}