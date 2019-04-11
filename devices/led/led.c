//
// Created by 민지우 on 2019-04-12.
//

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdarg.h>

#include "../../services/log/log.h"
#include "./led_itf.h"
#include "./led.h"

#define IOM_LED_ADDRESS 0x08000016

callback LED_CALLBACK[NUM_CALLBACK_LED] = {cb_light_led};

static int fd = -1;
static unsigned long *ledaddr = 0;

int open_led () {
    fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0) {
        LOG_ERROR("Fail:: open led: /dev/mem");
        return LED_ERROR;
    }

    ledaddr = (unsigned long *) mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, IOM_LED_ADDRESS);
    if (ledaddr == NULL) {
        LOG_ERROR("Fail:: led: mmap error");
        close(fd);
        return LED_ERROR;
    }

    return LED_SUCCESS;
}

int close_led () {
    munmap(ledaddr, 4096);
    close(fd);
    return LED_SUCCESS;
}

int light_led (unsigned char val) {
//    *ledaddr = val;

    LOG_INFO("Light change %X", val);

    return LED_SUCCESS;
}

int cb_light_led (int cnt, ...) {
    va_list ap;
    va_start(ap, cnt);

    return light_led(*va_arg(ap, char *));
}