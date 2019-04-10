//
// Created by 민지우 on 2019-04-10.
//

#ifndef EMBEDED_LOG_H
#define EMBEDED_LOG_H

#define LOG_NONE 0
#define LOG_ERROR 1
#define LOG_WARN 2
#define LOG_INFO 3
#define LOG_LEVEL LOG_WARN

int log_dev(char *msg);
int log_warn(char *msg);
int log_err(char *msg);

#endif //EMBEDED_LOG_H
