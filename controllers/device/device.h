//
// Created by 민지우 on 2019-04-11.
//
#include "../../services/callback.h"
#include "../../services/mq/mq.h"

#ifndef EMBEDED_DEVICE_H
#define EMBEDED_DEVICE_H

int open_drivers ();
int close_drivers ();
int exec_callback (MESSAGE);

#define NUM_DEVICE      4

#define DEVICE_FND      0
#define DEVICE_LED      1
#define DEVICE_LCD      2
#define DEVICE_DOT      3



#endif //EMBEDED_DEVICE_H
