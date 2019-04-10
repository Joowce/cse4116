//
// Created by 민지우 on 2019-04-10.
//
#include <signal.h>
#include <unistd.h>
#include "services/log/log.h"


int main (void) {
    pid_t p_main = getppid();
    LOG_INFO("input process exec");
    LOG_INFO("parent process:: %d", p_main);
    kill(p_main, SIGUSR1);
    return 0;
}