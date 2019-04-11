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
    msgbuf* message = (msgbuf *)malloc(sizeof(msgbuf));

    LOG_INFO("exec output process");
    LOG_INFO("output process:: parent pid: %d", ppid);

    create_message_queue();
//    if(open_drivers() == -1) {
//        LOG_ERROR("fail open drivers, kill output process");
//        exit(0);
//    }


    while(1) {
         if (get_message(message) == -1) {
             LOG_INFO("No message");
             continue;
         }

         if (message -> data.device_type == NUM_DEVICE) {
             LOG_INFO("end output process");
             break;
         }

         LOG_INFO("got message, try to execute call back :: %d, %d, %d", message->data.device_type, message->data.callback_num, message->data.arg_cnt);
         exec_callback(message->data);
    }

    close_drivers();
    remove_message_queue();
    return 0;
}