//
// Created by 민지우 on 2019-04-12.
//

#include "sender.h"
#include "../input_itf.h"
#include "../../../services/shared_memory/shared_memory.h"
#include "../../../services/signal/signal.h"
#include "../../../services/log/log.h"

int send_read_key (pid_t pid, char key_code) {
    if(write_shm(SHM_ADDR_BUTT, (char *)&key_code, sizeof(char)) == SHM_ERROR) {
        LOG_ERROR("can't write read_key code");
        return INPUT_ERROR;
    }

    LOG_INFO("write read_key code to shared memory");

    send_signal(pid, SIGUSR1);
    LOG_INFO("send signal#[%d] to [%d] process", SIGUSR1, pid);

    return INPUT_SUCCESS;
}