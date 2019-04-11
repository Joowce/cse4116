//
// Created by 민지우 on 2019-04-11.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "./services/log/log.h"
#include "./controllers/device/device.h"

int main (void) {
    int ppid = getppid();
    MESSAGE* message;

    LOG_INFO("exec output process");
    LOG_INFO("output process:: parent pid: %d", ppid);

//    if(open_drivers() == -1) {
//        LOG_ERROR("fail open drivers, kill output process");
//        exit(0);
//    }

    while(1) {
         message = get_message();

         if (message == NULL) {
             LOG_INFO("No message");
             continue;
         }
         if (message -> device_type == NUM_DEVICE) {
             LOG_INFO("end output process");
             break;
         }

         LOG_INFO("got message, try to exec call back :: %d, %d, %d", message->device_type, message->callback_num, message->arg_cnt);
         exec_callback(*message);
    }

    close_drivers();
    return 0;
}