//
// Created by 민지우 on 2019-04-11.
//
#include "../../services/callback.h"
#include "../../services/mq/mq.h"
#include "./itf.h"


#ifndef EMBEDED_DEVICE_H
#define EMBEDED_DEVICE_H

int open_drivers ();
int close_drivers ();
int exec_callback (MESSAGE);



typedef struct {
    callback_no_arg open;
    callback_no_arg close;
    callback*        callbacks;
} device_itf;

extern device_itf DEVICE_TABLE [NUM_DEVICE];

#endif //EMBEDED_DEVICE_H
