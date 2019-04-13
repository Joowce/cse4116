//
// Created by 민지우 on 2019-04-13.
//

#include "mode.h"

#include "../../services/log/log.h"

#include "../../mode/clock/clock.h"

#define MODE_CLOCK  0

typedef struct{
    int num;
    int (*init)(void);
    int (*exit)(void);
    int (*exec)(void);
}mode;

static mode MODE_TABLE[MODE_NUM] = {
        {MODE_CLOCK, clock_init, clock_exit, clock_init}
};

static int MODE_TYPE = MODE_CLOCK;

int is_valid_mode_num (int num) {
    return num >= 0 && num < MODE_NUM;
}

int mode_exit(int num) {
    if (!is_valid_mode_num(num)) return MODE_ERROR;
    return MODE_TABLE[num].exit();
}

int mode_init(int num) {
    if (!is_valid_mode_num(num)) return MODE_ERROR;
    return MODE_TABLE[num].init();
}

int mode_change(int val, int prev) {
    int result = MODE_SUCCESS;
    if(is_valid_mode_num(prev)) result = mode_exit(prev);
    if(is_valid_mode_num(val)) result &= mode_init(val);
    return result;
}

int mode_start() {
    return mode_init(MODE_TYPE);
}

int mode_end() {
    return mode_exit(MODE_TYPE);
}

int mode_execute() {
    if (!is_valid_mode_num(MODE_TYPE)) return MODE_ERROR;

    LOG_INFO("mode:: #[%d] mode execute", MODE_TYPE);
    return MODE_TABLE[MODE_TYPE].exec();
}

int mode_next() {
    int before = MODE_TYPE++;

    MODE_TYPE %= MODE_NUM;
    return mode_change(MODE_TYPE, before);
}

int mode_prev() {
    int before = MODE_TYPE--;

    MODE_TYPE %= MODE_NUM;
    return mode_change(MODE_TYPE, before);
}
