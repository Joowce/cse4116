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

/**
 * 1. get signal
 * 2. get rk code #
 * 3. execute handler of rk code#
 * @param signo
 */
void execute_rk (int signo) {
    int rk = get_rk_code();

    LOG_INFO("CTRL_RECEIVER:: read key code [%d]", rk);

    if(rk_handlers[rk] == NULL){
        LOG_ERROR("CTRL_RECEIVER:: no handler with [%d] read key", rk);
        return;
    }

    rk_handlers[rk]();
}

/**
 * 1. get signal
 * 2. get sw#
 * 3. execute handler of sw#
 * @param signo
 */
void execute_sw (int signo) {
    int sw = get_switch_button();

    LOG_INFO("CTRL_RECEIVER:: switch button code [%d]", sw);

    if(sw_handlers[sw] == NULL){
        LOG_ERROR("CTRL_RECEIVER:: no handler with [%d] button",sw);
        return;
    }
    sw_handlers[sw]();
}

/**
 * add read key signal handler
 * SIGNAL #: SIGUSR1
 * handler: execute rk
 * @return
 */
int init_rk_sig () {
    sigset_t set;

    sigfillset(&set);
    sigprocmask(SIGUSR2, &set, NULL);

    create_signal_action(SIGUSR1, execute_rk, &set);

    LOG_INFO("CTRL_RECEIVER:: initial read key receiver");

    return RECEIVER_SUCCESS;
}

/**
 * add switch button signal handler
 * SIGNAL #: SIGUSR2
 * handler: excute_sw
 * @return
 */
int init_sw_sig() {
    sigset_t set;

    sigfillset(&set);

    create_signal_action(SIGUSR2, execute_sw, &set);
    LOG_INFO("CTRL_RECEIVER:: initial switch receiver");
    return RECEIVER_SUCCESS;
}

/**
 * add read key handler
 * @param rk_code : # of read key code
 * @param handler : handler to add
 * @return
 */
int add_rk_handler(int rk_code, callback_no_arg handler) {
    if (rk_code < 0 && rk_code >= RK_NUM) return RECEIVER_ERROR;

    rk_handlers[rk_code] = handler;
    LOG_INFO("rk_handler:: Success to add handler");
    return RECEIVER_SUCCESS;
}

/**
 * add switch button handler
 * @param sw_num : # of switch
 * @param handler : handler to add
 * @return
 */
int add_sw_handler(int sw_num, callback_no_arg handler) {
    if (sw_num < 0 && sw_num >= SWITCH_NUM) return RECEIVER_ERROR;

    sw_handlers[sw_num] = handler;
    LOG_INFO("sw_handler:: Success to add handler");
    return RECEIVER_SUCCESS;
}


/**
 * remove switch handlers
 * @return
 */
int remove_sw_handler() {
    int i;
    for (i=0; i<SWITCH_NUM; i++) {
        sw_handlers[i] = NULL;
    }
    LOG_INFO("sw_handler:: Success remove switch handler");
    return RECEIVER_SUCCESS;
}

/**
 * remove read key handler
 * @return
 */
int remove_rk_handler() {
    int i;
    for (i=0; i < RK_NUM; i++) {
        rk_handlers[i] = NULL;
    }
    LOG_INFO("rk_handler:: Success remove read key handler");
    return RECEIVER_SUCCESS;
}