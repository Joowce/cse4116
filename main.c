#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <signal.h>

#include "services/log/log.h"
#include "services/proc.h"
#include "services/mq/mq.h"

#include "controllers/device/client/device_client.h"
#include "devices/led/light.h"


/**
 * 초기화
 * 1. 메세지 큐 생성
 * 2. shared memory 생성
 * 3. 첫번째 모드 설정
 * @return
 */
int initialize () {
    if(create_message_queue() == -1) return -1;

    return 1;
}

int main() {
//    pid_t p_input;
    pid_t p_output;
    unsigned char data[10] = {0x3e,0x7f,0x63,0x73,0x73,0x6f,0x67,0x63,0x7f,0x3e};

    initialize();

//    p_input = execf("input");
//    LOG_INFO("forked input process: %d", p_input);

    p_output = execf("output");
    LOG_INFO("forked output process: %d", p_output);

    unsigned char string[4] = {1,1,1,1};
    print_fnd(string);
    msgbuf* msg = create_message(4, 0, 0, NULL);

    if(send_message(msg) == -1) kill(p_output, SIGUSR1);
    return 0;
}


