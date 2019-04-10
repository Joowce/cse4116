//
// Created by 민지우 on 2019-04-10.
//

#ifndef EMBEDED_PROC_H
#define EMBEDED_PROC_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "log/log.h"

pid_t execf (char* name) {
    pid_t pid = fork();

    if (pid == 0) {
        execvp(name, NULL);
    } else if (pid == -1) {
        LOG__ERROR("fail to fork process");
        exit(0);
    } else {
        LOG__INFO("success fork process %d", pid);
    }

    return pid;
}

#endif //EMBEDED_PROC_H
