//
// Created by 민지우 on 2019-04-12.
//
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>

#include "lcd.h"
#include "lcd_itf.h"
#include "../../services/log/log.h"


#define FPGA_TEXT_LCD_DEVICE "/dev/fpga/text_lcd"

const callback LCD_CALLBACK[NUM_CALLBACK_LCD] = {cb_print_lcd};

static int dev = -1;

int open_lcd() {
    if (dev != -1) return dev;

    dev = open(FPGA_TEXT_LCD_DEVICE, O_WRONLY);
    if (dev < 0) {
        LOG_ERROR("Fail:: open LCD driver");
        return LCD_ERROR;
    }

    LOG_INFO("Success:: open LCD driver");
    return dev;
}

int close_lcd() {
    if (dev == -1) return LCD_SUCCESS;

    close(dev);
    LOG_INFO("Success:: close LCD driver");
    return LCD_SUCCESS;
}

int print_lcd (unsigned char* string) {
    dev = open_lcd();
    if (dev == -1) return LCD_ERROR;

    write(dev, string, LCD_MAX_BUFF);
    LOG_INFO("LCD print:: %s", string);
    return LCD_SUCCESS;
}

int cb_print_lcd (int cnt, ...) {
    va_list ap;
    va_start(ap, cnt);

    return print_lcd(va_arg(ap, unsigned char *));
}