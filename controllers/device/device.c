//
// Created by 민지우 on 2019-04-11.
//
#include <stdio.h>

#include "../../devices/dot/dot.h"
#include "../../devices/led/led.h"
#include "../../devices/lcd/lcd.h"

#include "../../services/log/log.h"
#include "device.h"


device_itf DEVICE_TABLE [NUM_DEVICE] = {
        {OPEN_LCD, CLOSE_LCD, (callback*)LCD_CALLBACK},
        {OPEN_LED, CLOSE_LED, (callback*)LED_CALLBACK},
        {OPEN_DOT, CLOSE_DOT, (callback*)DOT_CALLBACK}
};


int open_drivers () {
    int i;
    for (i = 0; i < NUM_DEVICE; i++) {
        if(DEVICE_TABLE[i].open() == -1) return -1;
    }
    return 1;
}

int close_drivers () {
    int i;
    for (i=0; i < NUM_DEVICE; i++) {
        if(DEVICE_TABLE[i].close() == -1) return -1;
    }
    return 1;
}

int exec_callback (MESSAGE message) {
    callback cb = DEVICE_TABLE[message.device_type].callbacks[message.callback_num];

    if (cb == NULL) {
        LOG_ERROR("No callback function:: device: %D, callback#: %d", message.device_type, message.callback_num);
        return -1;
    }

    return cb(message.arg_cnt, message.data);
}