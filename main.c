#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>

#include "services/log/log.h"
#include "services/proc.h"
#include "services/mq/mq.h"
#include "services/shared_memory/shared_memory.h"
#include "services/signal/signal.h"

#include "controllers/device/client/device_client.h"
#include "controllers/input/receiver/receiver.h"
#include "controllers/mode/mode.h"

#include "devices/read_key/rk_itf.h"

#define RUNNING 1
#define STOP    0

static int MAIN_STATE = RUNNING;
static pid_t p_input = -1;
static pid_t p_output = -1;

void kill_process (pid_t pid) {
    send_signal(pid, SIGINT);
}

int stop_main_state () {
    kill_process(p_input);
    LOG_INFO("main:: kill input process");

    kill_process(p_output);
    LOG_INFO("main::kill output process");
    return 1;
}

void stop_main (int signo) {
    stop_main_state();
}

/**
 * 초기화
 * 1. 메세지 큐 생성
 * 2. shared memory 생성
 * 3. rk handler 등록
 * 4. 첫번째 모드 설정
 * 5. signal SIGUSR1, SIGUSR2 설정
 * @return
 */
int initialize () {
    sigset_t set;
    if(create_message_queue() == -1) return -1;
    if(create_shm() == NULL) return -1;

    if(remove_rk_handler() == -1) return -1;
    if(remove_sw_handler() == -1) return -1;

    add_rk_handler(RK_BACK, stop_main_state);
    add_rk_handler(RK_VOL_DOWN, mode_prev);
    add_rk_handler(RK_VOL_UP, mode_next);

    sigemptyset(&set);
    create_signal_action(SIGINT, stop_main, &set);

    mode_start();

    init_rk_sig();
    init_sw_sig();


    return 1;
}

/**
 * 종료
 * 1. signal USR1, USR2 삭제
 * 2. 현재 진행중인 모드 종료
 * 3. 메시지 큐 삭제
 * 4. shared memory 삭제
 * 5. rk handler 삭제
 * @return
 */
int main_exit() {
    ignore_signal(SIGUSR1);
    ignore_signal(SIGUSR2);
    LOG_INFO("main:: ignore SIGUSR");

    mode_end();
    remove_message_queue();
    remove_shm();

    remove_rk_handler();
    remove_sw_handler();

    LOG_INFO("main:: Success exit main process");
    return 1;
}

int main() {
    int status;

    initialize();

    p_input = execf("input");
    LOG_INFO("forked input process: %d", p_input);

    p_output = execf("output");
    LOG_INFO("forked output process: %d", p_output);

//    while(MAIN_STATE) {
//        mode_execute();
//    }

    wait(&status);
    LOG_INFO("main:: end wait status: [%d]", status);

    main_exit();
    return 0;
}


