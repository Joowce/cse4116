//
// Created by 민지우 on 2019-04-12.
//
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

#include "read_key.h"
#include "../../services/log/log.h"
#include "rk_itf.h"

#define KEY_PRESS   1
#define KEY_RELEASE 0

#define BUFF_SIZE 64

#define FND_RK  "/dev/input/event0"

static int fd = -1;
static int pressed_rk = RK_ERROR;

int open_rk () {
    if (fd != -1) return fd;

    fd = open(FND_RK, O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        LOG_ERROR("read key:: Fail to open driver");
        return RK_ERROR;
    }

    LOG_INFO("read key:: Success to open driver");

    return fd;
}

int close_rk () {
    if (fd == -1) return RK_SUCCESS;

    if (close(fd) == -1) {
        LOG_ERROR("read key:: Fail to close driver");
        return RK_ERROR;
    }

    LOG_INFO("read key:: Success to close driver");
    fd = -1;
    return RK_SUCCESS;
}


int get_pressed_rk () {
    struct input_event ev[BUFF_SIZE];
    int result;

    int rd = read(fd, ev, sizeof(struct input_event) * BUFF_SIZE);

    if(rd < sizeof(struct input_event)) return RK_ERROR;

    if (pressed_rk == RK_ERROR) {
        if (ev[0].value == KEY_RELEASE) return RK_ERROR;

            pressed_rk = ev[0].code;
        return RK_ERROR;
    }

    if (ev[0].code != pressed_rk || ev[0].value == KEY_PRESS) return RK_ERROR;

    switch (pressed_rk) {
        case RK_CODE_BACK: result = RK_BACK; break;
        case RK_CODE_VOL_DOWN: result = RK_VOL_DOWN; break;
        case RK_CODE_VOL_UP: result = RK_VOL_UP; break;
        default: result = RK_ERROR; break;
    }

    pressed_rk = RK_ERROR;
    return result;
}


