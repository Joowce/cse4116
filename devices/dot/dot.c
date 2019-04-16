//
// Created by 민지우 on 2019-04-10.
//
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>

#include "./font.h"
#include "../../services/log/log.h"
#include "./dot.h"

#define FPGA_DOT_DEVICE "/dev/fpga_dot"

const callback DOT_CALLBACK[NUM_CALLBACK_DOT] = {cb_print_dot, cb_print_dot_num};
static int dev = -1;

/**
 * dot matrix driver open
 * @return
 */
int open_dot () {
    if (dev != -1) return dev;
    dev = open(FPGA_DOT_DEVICE, O_WRONLY);
    if (dev<0) {
        LOG_ERROR("DEVICE::dot: Device open error: %s", FPGA_DOT_DEVICE);
        return -1;
    }
    return dev;
}

/**
 * dot matrix driver close
 * @return
 */
int close_dot () {
    if(dev >= 0) close(dev);
    return 1;
}

/**
 * print dot matrix
 * @param data
 * @return
 */
static int print_dot (const unsigned char* data) {
    int str_size;

    dev = open_dot();
    if (dev < 0) return -1;

    str_size=sizeof(char) * DOT_SIZE;
    write(dev,data,str_size);
    LOG_INFO("DEVICE::dot:print:: %.*s", DOT_SIZE, data);

    return 1;
}

/**
 * print dot matrix number
 * @param num
 * @return
 */
static int print_dot_num (int num) {
    if (num < 0 || num > 9) {
        LOG_ERROR("DEVICE::dot:Invalid number, %d", num);
        return -1;
    }

    return print_dot(dot_number[num]);
}


int cb_print_dot(int cnt, ...) {
    va_list ap;
    unsigned char * message;

    va_start(ap, cnt);
    message = va_arg(ap, unsigned char *);
    int result = print_dot(message);
    va_end(ap);

    return result;
}

int cb_print_dot_num(int cnt, ...) {
    va_list ap;
    int * num;

    va_start(ap, cnt);
    num = va_arg(ap, int*);
    int result = print_dot_num(*num);
    va_end(ap);

    return result;
}
