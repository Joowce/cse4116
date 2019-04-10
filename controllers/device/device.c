//
// Created by 민지우 on 2019-04-11.
//

#include "../../devices/dot/dot.h"
#include "device.h"

static const callback_no_arg OPEN[NUM_DEVICE] = {OPEN_DOT};
static const callback_no_arg CLOSE[NUM_DEVICE] = {CLOSE_DOT};

static const callback* CALLBACK_DEVICE[NUM_DEVICE] = {DOT_CALLBACK};


int open_drivers () {
    int i;
    for (i = 0; i < NUM_DEVICE; i++) {
        if(OPEN[i]() == -1) return -1;
    }
    return 1;
}

int close_drivers () {
    int i;
    for (i=0; i < NUM_DEVICE; i++) {
        if(CLOSE[i]() == -1) return -1;
    }
    return 1;
}

int exec_callback (MESSAGE message) {
    return CALLBACK_DEVICE[message.device_type][message.callback_num](message.arg_cnt, message.data);
}