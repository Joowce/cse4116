//
// Created by 민지우 on 2019-04-12.
//
#include <stdlib.h>

#include "lcd.h"
#include "../../../services/mq/mq.h"
#include "../itf.h"
#include "../../../devices/lcd/lcd_itf.h"
#include "../../../services/log/log.h"

int print_lcd (unsigned char* string) {
    msgbuf *buf = create_message(DEVICE_LCD, PRINT_LCD, 1, string);
    int result = send_message(buf);
    if (result == MQ_ERROR) {
        LOG_ERROR("Fail:: print dot: can't send message");
    }
    free(buf);

    return result;
}