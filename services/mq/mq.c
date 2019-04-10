//
// Created by 민지우 on 2019-04-10.
//
#include <stdlib.h>

#include "mq.h"


MESSAGE* get_message () {
    MESSAGE* message = (MESSAGE *) malloc(sizeof(MESSAGE));
    message->device_type = 4;
    return message;
}