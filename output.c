//
// Created by 민지우 on 2019-04-11.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#include "./services/log/log.h"
#include "./controllers/device/device.h"
#include "services/signal/signal.h"

#define RUNNING 1
#define STOP    0

static int OUTPUT_STATE = RUNNING;

void stop_output_state (int signo) {
    OUTPUT_STATE = STOP;
}

int main (void) {
    int ppid = getppid();
    msgbuf* message = (msgbuf *)malloc(sizeof(msgbuf));

    reg_signal_handler(SIGINT, stop_output_state);

    LOG_INFO("OUTPUT:: start output process");
    LOG_INFO("OUTPUT:: parent pid: %d", ppid);

    create_message_queue();
    if(open_drivers() == -1) {
        LOG_ERROR("OUTPUT:: Fail open drivers, exit output process");
        exit(0);
    }




    while(OUTPUT_STATE) {
         if (get_message(message) == -1) {
             LOG_INFO("OUTPUT:: No message");
             continue;
         }

         if (message -> data.device_type == NUM_DEVICE) {
             LOG_INFO("end output process");
             break;
         }

         LOG_INFO("OUTPUT:: got message, try to execute call back :: %d, %d, %d", message->data.device_type, message->data.callback_num, message->data.arg_cnt);
         exec_callback(message->data);
    }

    close_drivers();
    remove_message_queue();

    LOG_INFO("-------- End OUTPUT --------");
    return 0;
}