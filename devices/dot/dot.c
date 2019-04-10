//
// Created by 민지우 on 2019-04-10.
//
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include "./font.h"
#include "../../services/log/log.h"

#define FPGA_DOT_DEVICE "/dev/fpga_dot"


int print_dot (const unsigned char* data) {
    int dev;
    int str_size;
    dev = open(FPGA_DOT_DEVICE, O_WRONLY);
    if (dev<0) {
        LOG_ERROR("DEVICE::dot: Device open error: %s", FPGA_DOT_DEVICE);
        return -1;
    }
    str_size=sizeof(data);
    write(dev,data,str_size);

    close(dev);
    return 1;
}


int print_dot_num (int num) {
    if (num < 0 || num > 9) {
        LOG_ERROR("DEVICE::dot:Invalid number, %d", num);
        return -1;
    }

    return print_dot(fpga_number[num]);
}


