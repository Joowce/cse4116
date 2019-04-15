//
// Created by 민지우 on 2019-04-12.
//

#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>


#include "fnd.h"
#include "../../services/log/log.h"
#include "./fnd_itf.h"


#define FPGA_FND_DEVICE "/dev/fpga_fnd"

const callback FND_CALLBACK[NUM_CALLBACK_FND] = {cb_print_fnd};

static int dev = -1;

int open_fnd() {
    if (dev != -1) return dev;

    dev = open(FPGA_FND_DEVICE, O_RDWR);
    if (dev < 0) {
        LOG_ERROR("Fail:: open FND driver");
        return FND_ERROR;
    }

    LOG_INFO("Success:: open FND driver");
    return dev;
}

int close_fnd() {
    if (dev == -1) return FND_SUCCESS;

    close(dev);
    LOG_INFO("Success:: close FND driver");
    return FND_SUCCESS;
}

int print_fnd (unsigned char* string) {
    dev = open_fnd();
    if (dev == -1) return FND_ERROR;

    write(dev, string, FND_MAX_DIGIT);
    LOG_INFO("FND print:: %d %d %d %d", string[0], string[1], string[2], string[3]);
    return FND_SUCCESS;
}

int cb_print_fnd (int cnt, ...) {
    va_list ap;
    va_start(ap, cnt);

    return print_fnd(va_arg(ap, unsigned char *));
}