//
// Created by 민지우 on 2019-04-13.
//

#include "mode.h"

#include "../../services/log/log.h"
#include "../../services/timer/timer.h"

#include "../../controllers/device/client/device_client.h"

#include "../../mode/clock/clock.h"
#include "../../mode/counter/counter.h"
#include "../../mode/editer/editor.h"

#define MODE_CLOCK      0
#define MODE_COUNTER    1
#define MODE_EDITOR     2

typedef struct{
    int num;
    int (*init)(void);
    int (*exit)(void);
}mode;

static int is_valid_mode_num (int num);
static int mode_init(int num);
static int mode_exit(int num);
static int mode_change(int, int);


static mode MODE_TABLE[MODE_NUM] = {
        {MODE_CLOCK, clock_init, clock_exit},
        {MODE_COUNTER, counter_init, counter_exit},
        {MODE_EDITOR, editor_init, editor_exit}
};
static int MODE_TYPE = MODE_CLOCK;




int mode_start() {
    return mode_init(MODE_TYPE);
}

int mode_end() {
    return mode_exit(MODE_TYPE);
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




int is_valid_mode_num (int num) {
    return num >= 0 && num < MODE_NUM;
}

int mode_init(int num) {
    if (!is_valid_mode_num(num)) return MODE_ERROR;

    LOG_INFO("CTRL_mode:: mode[%d] initialize", num);
    return MODE_TABLE[num].init();
}

int mode_exit(int num) {
    if (!is_valid_mode_num(num)) return MODE_ERROR;

    LOG_INFO("CTRL_mode:: mode[%d] exit", num);
    if(MODE_TABLE[num].exit() == -1) {
        LOG_ERROR("CTRL_mode:: fail to exit mode");
        return -1;
    }

    dvice_init();
    timer_cancel();
    return 1;
}


int mode_change(int val, int prev) {
    int result = MODE_SUCCESS;
    if(is_valid_mode_num(prev)) result = mode_exit(prev);
    if(is_valid_mode_num(val)) result &= mode_init(val);
    return result;
}

