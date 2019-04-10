//
// Created by 민지우 on 2019-04-10.
//

#include <stdio.h>
#include <string.h>
#include "log.h"

// 로그 레벨별로 관리
int log(char *msg, int level){
    if (LOG_LEVEL >= level) {
        printf("LOG %d: %s\n", level, msg);
    }

    return 0;
}


int log_dev(char *msg) {
    char buf[100];
    sprintf(buf, "INFO:: %s", msg);
    log(msg, LOG_INFO);
    return 0;
}

int log_warn (char *msg) {
    char buf[100];
    sprintf(buf, "WARNING:: %s", msg);
    log(msg, LOG_WARN);
    return 0;
}

int log_err (char *msg) {
    char buf[100];
    sprintf(buf, "ERROR:: %s", msg);
    log(buf, LOG_ERROR);
    return 0;
}