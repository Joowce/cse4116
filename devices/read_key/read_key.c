//
// Created by 민지우 on 2019-04-12.
//
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

#include "read_key.h"
#include "../../services/log/log.h"

#define KEY_PRESS   1
#define KEY_RELEASE 0

#define BUFF_SIZE 64

#define FND_RK  "/dev/input/event0"

static int fd = -1;

int open_rk () {
    if (fd != -1) return fd;

    fd = open(FND_RK, O_RDONLY);
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


int get_rk () {
    struct input_event ev[BUFF_SIZE];
    int rd = read(fd, ev, sizeof(struct input_event) * BUFF_SIZE);

    if(rd < sizeof(struct inpue_event)) return RK_ERROR;

    LOG_INFO("read key:: Type[%d] Value[%d] Code[%d]", ev[0].type, ev[0].value, ev[0].code);

    return ev[0].code;
}


