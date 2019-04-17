//
// Created by 민지우 on 2019-04-13.
//
#include <fcntl.h>
#include <unistd.h>

#include "switch.h"
#include "switch_itf.h"
#include "../../services/log/log.h"


#define FPGA_SWITCH "/dev/fpga_push_switch"

#define NUM_BUTTON  9
#define PRESSED     1
#define RELEASED    0


static int dev = -1;
static int pressed_button = SWITCH_ERROR;
unsigned int switch_status [SWITCH_NUM];

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


unsigned int get_sw_mask (int num) {
    return 1 << num;
}

int get_switch_status (const unsigned char* switch_buttons) {
    int i;
    int temp = 0;
    if (switch_status[0] == 0) {
        for(i = 0; i < NUM_BUTTON; i++) {
            switch_status[i] = get_sw_mask(i);
        }
        switch_status[SW10] = switch_status[SW2] | switch_status[SW3];
        switch_status[SW11] = switch_status[SW5] | switch_status[SW6];
        switch_status[SW12] = switch_status[SW8] | switch_status[SW9];
    }

    for (i = 0; i < NUM_BUTTON; i++) {
        if (switch_buttons[i] == PRESSED) {
            temp |= switch_status[i];
        }
    }

    for (i = 0; i < SWITCH_NUM; i++) {
        if ((temp ^ switch_status[i]) == 0) {
            return i;
        }
    }
    return SWITCH_ERROR;
}

int get_pressed_switch () {
    unsigned char switch_buttons[SWITCH_NUM];
    int i, cur_switch_status;
    read(dev, switch_buttons, sizeof(switch_buttons));
    cur_switch_status = get_switch_status(switch_buttons);

    if (pressed_button == SWITCH_ERROR) {
        pressed_button = cur_switch_status;
        return SWITCH_ERROR;
    }

    if (cur_switch_status == pressed_button) return SWITCH_ERROR;

    i = pressed_button;
    pressed_button = cur_switch_status;

    return i;
}