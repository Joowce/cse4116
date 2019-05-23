//
// Created by 민지우 on 2019-04-10.
//

#include <stdio.h>

#include "signal.h"
#include "../log/log.h"

int reg_signal_handler(int signo, void (*handler) (int)) {

    signal(signo,handler);
    return 1;
}

void send_signal (pid_t pid, int sig) {
    kill(pid, sig);
    LOG_INFO("signal:: send [%d] signal to [%d] process", sig, pid);
}

void ignore_signal (int sig) {
    signal(sig, SIG_IGN);
}