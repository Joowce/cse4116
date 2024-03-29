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
#include "light.h"

#define FPGA_BASE_ADDRESS 0x08000000
#define LED_ADDR 0x16


const callback LED_CALLBACK[NUM_CALLBACK_LED] = {cb_light_led};

static int fd = -1;
static unsigned char *ledaddr = 0;

int open_led () {
    unsigned long *fpga_base_addr;
    fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0) {
        LOG_ERROR("LED::Fail to open led: /dev/mem");
        return LED_ERROR;
    }

    fpga_base_addr = (unsigned long *)mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, FPGA_BASE_ADDRESS);
    if (fpga_base_addr == MAP_FAILED) {
        LOG_ERROR("LED:: Fail mmap error");
        close(fd);
        return LED_ERROR;
    }

    ledaddr = (unsigned char*)((void*)fpga_base_addr+LED_ADDR);
    LOG_INFO("LED:: Success to open mmap");
    return LED_SUCCESS;
}

int close_led (){
    *ledaddr = LED_OFF;
    munmap(ledaddr, 4096);
    close(fd);

    LOG_INFO("LED:: Success to close mmap");
    return LED_SUCCESS;
}

int light_led (unsigned char val) {
    *ledaddr = val;
    LOG_INFO("LED:: change %X", val);

    return LED_SUCCESS;
}

int cb_light_led (int cnt, ...) {
    va_list ap;
    unsigned char arg;

    va_start(ap, cnt);
    arg = *va_arg(ap, unsigned char*);
    return light_led(arg);
}