//
// Created by 민지우 on 2019-04-10.
//

#ifndef EMBEDED_PROC_H
#define EMBEDED_PROC_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log/log.h"

pid_t execf (char* name) {
    char buff[BUFSIZ];
    char* cwd;
    pid_t pid = fork();

    if (pid == 0) {
        cwd = getcwd(buff, BUFSIZ);
        strcat(cwd, "/"); strcat(cwd, name);
        LOG__INFO("TRY EXECVP %s in %s", name, cwd);
        execl(cwd, name, NULL);
    } else if (pid == -1) {
        LOG__ERROR("fail to fork process");
        exit(0);
    } else {
        LOG__INFO("success fork process %d", pid);
    }

    return pid;
}

#endif //EMBEDED_PROC_H
