//
// Created by 민지우 on 2019-04-10.
//
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>

#include "./font.h"
#include "../../services/log/log.h"

#define FPGA_DOT_DEVICE "/dev/fpga_dot"

static int dev = -1;

int open_dot () {
    if (dev != -1) return dev;
    dev = open(FPGA_DOT_DEVICE, O_WRONLY);
    if (dev<0) {
        LOG_ERROR("DEVICE::dot: Device open error: %s", FPGA_DOT_DEVICE);
        return -1;
    }
    return dev;
}

int close_dot () {
    if(dev >= 0) close(dev);
    return 1;
}


static int print_dot (const unsigned char* data) {
    int str_size;

    dev = open_dot();
    if (dev < 0) return -1;

    str_size=sizeof(data);
    write(dev,data,str_size);

    return 1;
}

static int print_dot_num (int num) {
    if (num < 0 || num > 9) {
        LOG_ERROR("DEVICE::dot:Invalid number, %d", num);
        return -1;
    }

    return print_dot(fpga_number[num]);
}


int cb_print_dot(int cnt, ...) {
    va_list ap;

    va_start(ap, cnt);
    int result = print_dot((unsigned char *)ap);
    va_end(ap);

    return result;
}

int cb_print_dot_num(int cnt, ...) {
    va_list ap;
    va_start(ap, cnt);
    int result = print_dot_num((int) ap);
    va_end(ap);
    return result;
}