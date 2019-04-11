//
// Created by 민지우 on 2019-04-10.
//

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <stdarg.h>
#include <stdlib.h>

#include "log.h"

static int  log_level = LOG_LVL_DEBUG;

/**
* log level을 조정합니다.
*/
int LOGsetLevel(int log_lvl)
{
    int tmp = LOGgetLevel();

    log_level = log_lvl;

    return tmp;
}

/**
* log level을 최초로 요청할 때에는 환경변수의 설정을 읽습니다.
*/
int LOGgetLevel(void)
{
    char *log_env;
    static int is_env_check = 0;

    if(is_env_check == 0) {
        if((log_env = getenv("LOG_LEVEL")) == NULL) {
            log_level = LOG_LVL_INFO;
        } else {
            if(strcmp(log_env, "TRACE") == 0) {
                log_level = LOG_LVL_TRACE;
            } else if(strcmp(log_env, "DEBUG") == 0) {
                log_level = LOG_LVL_DEBUG;
            } else if(strcmp(log_env, "INFO") == 0) {
                log_level = LOG_LVL_INFO;
            } else if(strcmp(log_env, "WARNING") == 0) {
                log_level = LOG_LVL_WARNING;
            } else if(strcmp(log_env, "ERROR") == 0) {
                log_level = LOG_LVL_ERROR;
            } else if(strcmp(log_env, "FATAL") == 0) {
                log_level = LOG_LVL_FATAL;
            } else {
                log_level = LOG_LVL_INFO;
            }
        }
        is_env_check = 1;
    }
    return log_level;
}


/**
* LOGlogging(...) 로그 파일을 생성함.
* log_type, 로그생성일시분초microseconds, process id, 소스파일, 함수명, 라인수, 오류 내용
* 의 format으로 로그를 생성함.
*/
int LOGlogging(char log_type, const char *src_file, const char *func, int line_no, const char *fmt, ...)
{
    va_list ap;
    int  sz = 0;
    struct timeval tv;
    struct tm *tm1;
    static int   day = -1;
    static pid_t pid = -1;
    char   src_info[128];

    gettimeofday(&tv, NULL);
    tm1 = localtime(&tv.tv_sec);
    va_start(ap, fmt);

    if(pid == -1) {
        pid = getpid();
    }
    /* 날짜가 변경되었으면 또는 최초 실행시에  */
    if(day != tm1->tm_mday) day = tm1->tm_mday;

    sz += printf("(%c) ", log_type);
    sz += printf("%04d%02d%02d:%02d%02d%02d%06ld:%05d",
                  1900 + tm1->tm_year, tm1->tm_mon + 1, tm1->tm_mday,
                  tm1->tm_hour, tm1->tm_min, tm1->tm_sec, (long)tv.tv_usec, pid);
    snprintf(src_info, 128, "%s:%s(%d)", src_file, func, line_no);
    sz += printf(":%-50.50s: ", src_info);
    sz += vprintf(fmt, ap);
    sz += printf("\n");
    va_end(ap);

    return sz;
}
