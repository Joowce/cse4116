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


static int dev = -1;
static int prev_mask = 0;
unsigned int status_mask [SWITCH_NUM] = {0,};

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

int get_switch_mask (const unsigned char* switch_buttons) {
    int i;
    int mask = 0;
    if (status_mask[0] == 0) {
        for(i = 0; i < NUM_BUTTON; i++) {
            status_mask[i] = get_sw_mask(i);
        }
        status_mask[SW10] = status_mask[SW2] | status_mask[SW3];
        status_mask[SW11] = status_mask[SW5] | status_mask[SW6];
        status_mask[SW12] = status_mask[SW8] | status_mask[SW9];
    }

    for (i = 0; i < NUM_BUTTON; i++) {
        if (switch_buttons[i] == PRESSED) {
            mask |= status_mask[i];
        }
    }
    return mask;
}

int convert_switch_num(int mask) {
    int i=0;
    for (i = 0; i < SWITCH_NUM; i++) {
        if ((mask ^ status_mask[i]) == 0) {
            return i;
        }
    }
    return SWITCH_ERROR;
}

int get_pressed_switch () {
    unsigned char switch_buttons[NUM_BUTTON];
    int cur_status_mask;
    int switch_num;
    read(dev, switch_buttons, sizeof(switch_buttons));
    cur_status_mask = get_switch_mask(switch_buttons);

    if (prev_mask == 0) {
        prev_mask = cur_status_mask;
        return SWITCH_ERROR;
    }

    if ((cur_status_mask & prev_mask) > 0) return SWITCH_ERROR;

    switch_num = convert_switch_num(prev_mask);
    prev_mask = cur_status_mask;
    return switch_num;
}