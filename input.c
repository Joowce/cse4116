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
    sigset_t set;

    sigemptyset(&set);
    create_signal_action(SIGINT, stop_input_state, &set);

    open_rk();
    open_switch();

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

void clean_up_rk (void *) {
    close_rk();
}

void* run_rk (void* pid) {
    int rk;
    open_rk();
    pthread_cleanup_push(clean_up_rk, NULL)
    while(INPUT_STATE) {
        rk = get_pressed_rk();
        if (rk != RK_ERROR) send_read_key(*(int *)pid, (char)rk);
    }
    pthread_cleanup_pop(0)
    pthread_exit(NULL);
}


int main (void) {
    pid_t p_main = getppid();
    int t_id;
    int status;
    int switch_button;
    pthread_t pthread;

    LOG_INFO("exec input process");
    LOG_INFO("input process:: parent pid: %d", p_main);

    initial_input();

    t_id = pthread_create(&pthread, NULL, run_rk, (void *)&p_main);
    LOG_INFO("input:: thread create [%d]",t_id);

    while(INPUT_STATE) {
//        usleep(300);
//        rk = get_pressed_rk();
//        if (rk != RK_ERROR) send_read_key(p_main, (char) rk);

        switch_button = get_pressed_switch();
        if (switch_button != SWITCH_ERROR) send_switch_button(p_main, (char) switch_button);
    }

    pthread_cancel(pthread);
    pthread_join(pthread,(void *)&status);
    LOG_INFO("main:: thread exit with status [%d]", status);

    exit_input();
    return 0;
}