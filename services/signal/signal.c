//
// Created by 민지우 on 2019-04-10.
//

#include <stdio.h>
#include <signal.h>
#include "signal.h"

struct sigaction create_signal(int signo, void (*handler) (int), const sigset_t* sa_mask) {
    struct sigaction act;
    act.sa_handler = handler;

    if (sa_mask != NULL) act.sa_mask = *sa_mask;
    sigaction(signo, &act, NULL);

    return act;
}