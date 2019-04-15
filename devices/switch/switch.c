//
// Created by 민지우 on 2019-04-13.
//
#include <fcntl.h>
#include <unistd.h>

#include "switch.h"
#include "switch_itf.h"
#include "../../services/log/log.h"


#define FPGA_SWITCH "/dev/fpga_push_switch"

#define PRESSED     1
#define RELEASED    0

static int dev = -1;
static int pressed_button = SWITCH_ERROR;

int close_switch() {
    if (dev < 0) return SWITCH_SUCCESS;

    close(dev);
    dev = -1;

    LOG_INFO("switch:: close driver");

    return SWITCH_SUCCESS;
}

int open_switch() {
    if (dev != -1) return dev;

    dev = open(FPGA_SWITCH, O_RDWR);

    if (dev < 0) {
        LOG_ERROR("switch::Fail to open driver");
        close(dev);
        return SWITCH_ERROR;
    }

    LOG_INFO("switch::Success to open driver");

    return SWITCH_SUCCESS;
}

int get_pressed_switch () {
    unsigned char switch_buttons[SWITCH_NUM];
    int i;
    read(dev, switch_buttons, sizeof(switch_buttons));

    if (pressed_button == SWITCH_ERROR) {
        for (i =0 ; i < SWITCH_NUM; i++) {
            if (switch_buttons[i] == RELEASED) continue;

            pressed_button = i;
            break;
        }
        return SWITCH_ERROR;
    }

    if (switch_buttons[pressed_button] == PRESSED) return SWITCH_ERROR;

    i = pressed_button;
    pressed_button = SWITCH_ERROR;
    return i;
}