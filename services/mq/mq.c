//
// Created by 민지우 on 2019-04-10.
//
#include <stdlib.h>
#include <memory.h>

#include "mq.h"
#include "../../devices/dot/dot.h"


MESSAGE* get_message () {
    unsigned char m[10] = {0x3e,0x7f,0x63,0x73,0x73,0x6f,0x67,0x63,0x7f,0x3e};

    MESSAGE* message = (MESSAGE *) malloc(sizeof(MESSAGE));
    message->device_type = 0;
    message->callback_num = DOT_PRINT;
    message->arg_cnt = 1;

    memcpy(message->data, m, sizeof(m));
    return message;
}