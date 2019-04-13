//
// Created by 민지우 on 2019-04-13.
//
#include <stdlib.h>

#include "receiver.h"
#include "../input_itf.h"

#include "../../../devices/read_key/rk_itf.h"
#include "../../../devices/switch/switch_itf.h"

#include "../../../services/log/log.h"
#include "../../../services/signal/signal.h"
#include "../../../services/shared_memory/shared_memory.h"

static callback_no_arg rk_handlers[RK_NUM];
static callback_no_arg sw_handlers[SWITCH_NUM];

int get_rk_code () {
    char code = *(get_shm_addr() + SHM_ADDR_RK);
    return (int) code;
}

int get_switch_button () {
    char button = *(get_shm_addr() + SHM_ADDR_BUTT);
    return (int) button;
}

void execute_rk (signo) {
    int rk = get_rk_code();

    LOG_INFO("read key code [%d]", rk);

    if(rk_handlers[rk] == NULL){
        LOG_ERROR("read_key handler:: no handler with [%d] button", rk);
        return;
    }

    rk_handlers[rk]();
}

void execute_sw (int signo) {
    int sw = get_switch_button();

    LOG_INFO("switch button code [%d]", sw);

    if(sw_handlers[sw] == NULL){
        LOG_ERROR("switch handler:: no handler with [%d] button",sw);
        return;
    }
    sw_handlers[sw]();
}

int init_rk_sig () {
    sigset_t set;
    sigfillset(&set);
    sigprocmask(SIGUSR2, &set, NULL);
    create_signal_action(SIGUSR1, execute_rk, &set);
    return RECEIVER_SUCCESS;
}

int init_sw_sig() {
    sigset_t set;
    sigfillset(&set);
    create_signal_action(SIGUSR2, execute_sw, &set);
    return RECEIVER_SUCCESS;
}

int add_rk_handler(int rk_code, callback_no_arg handler) {
    if (rk_code < 0 && rk_code >= RK_NUM) return RECEIVER_ERROR;
    rk_handlers[rk_code] = handler;
    return RECEIVER_SUCCESS;
}

int add_sw_handler(int sw_num, callback_no_arg handler) {
    if (sw_num < 0 && sw_num >= SWITCH_NUM) return RECEIVER_ERROR;
    sw_handlers[sw_num] = handler;
    return RECEIVER_SUCCESS;
}

int remove_sw_handler() {
    int i;
    for (i=0; i<SWITCH_NUM; i++) {
        sw_handlers[i] = NULL;
    }
    return RECEIVER_SUCCESS;
}

int remove_rk_handler() {
    int i;
    for (i=0; i < RK_NUM; i++) {
        rk_handlers[i] = NULL;
    }
    return RECEIVER_SUCCESS;
}