//
// Created by 민지우 on 2019-04-13.
//
#include <fcntl.h>
#include <unistd.h>

#include "switch.h"
#include "switch_itf.h"
#include "../../services/log/log.h"

#define MAX_BUTTON  9
#define FPGA_SWITCH "/dev/fpga_push_switch"

#define PRESSED     1
#define RELEASED    0

static int dev = -1;
static int pressed_button = -1;

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
    unsigned char switch_buttons[MAX_BUTTON];
    int i;
    read(dev, &switch_buttons, sizeof(switch_buttons));

    if (pressed_button == -1) {
        for (i =0 ; i < MAX_BUTTON; i++) {
            if (switch_buttons[i] == RELEASED) continue;

            pressed_button = i;
            break;
        }
        return SWITCH_ERROR;
    }

    if (switch_buttons[pressed_button] == PRESSED) return SWITCH_ERROR;

    i = pressed_button;
    pressed_button = -1;
    return i;
}