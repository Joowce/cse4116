//
// Created by 민지우 on 2019-04-10.
//
#include <signal.h>
#include <unistd.h>
#include <pthread.h>

#include "services/log/log.h"
#include "services/signal/signal.h"
#include "services/shared_memory/shared_memory.h"

#include "controllers/input/sender/sender.h"

#include "devices/read_key/read_key.h"
#include "devices/switch/switch.h"
#include "devices/switch/switch_itf.h"

#define RUNNING 1
#define STOP    0

static int INPUT_STATE = RUNNING;

void stop_input_state (int signo) {
    INPUT_STATE = STOP;
}

/**
 * 초기화
 * 1. sigint 설정 (종료시 사용)
 * 2. shared memory 생성
 * 3. driver open
 */
int initial_input() {
    reg_signal_handler(SIGINT, stop_input_state);

    if(open_rk() == -1 || open_switch() == -1) return -1;

    if (create_shm() == NULL) return -1;
    return 1;
}

/**
 * 종료
 * 1. shared memory 삭제
 * 2. driver close
 * @return
 */
int exit_input() {
    remove_shm();
    close_rk();
    close_switch();
    return 1;
}


int main (void) {
    pid_t p_main = getppid();
    int rk;
    int switch_button;

    LOG_INFO("exec input process");
    LOG_INFO("input process:: parent pid: %d", p_main);

    if (initial_input() == -1) {
        LOG_ERROR("Error:: Fail initialize input process");
        exit(0);
    }

    while(INPUT_STATE) {
        usleep(300);
        rk = get_pressed_rk();
        if (rk != RK_ERROR) send_read_key(p_main, (char) rk);

        switch_button = get_pressed_switch();
        if (switch_button != SWITCH_ERROR) send_switch_button(p_main, (char) switch_button);
    }

    exit_input();
    return 0;
}