//
// Created by 민지우 on 2019-04-12.
//
#include <stdlib.h>

#include "led.h"
#include "../../../services/mq/mq.h"
#include "../itf.h"
#include "../../../devices/led/led_itf.h"
#include "../../../services/log/log.h"

int light_led (unsigned char val) {
    msgbuf *buf = create_message(DEVICE_LED, LIGHT_LED, 1, &val);
    int result = send_message(buf);
    if (result == MQ_ERROR) {
        LOG_ERROR("Fail:: print dot: can't send message");
    }
    free(buf);

    return result;
}