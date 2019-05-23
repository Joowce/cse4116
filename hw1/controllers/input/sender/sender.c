//
// Created by 민지우 on 2019-04-12.
//

#include "sender.h"
#include "../input_itf.h"
#include "../../../services/shared_memory/shared_memory.h"
#include "../../../services/signal/signal.h"
#include "../../../services/log/log.h"


typedef struct {
    char name[15];
    int addr;
    char data;
    pid_t pid;
    int sig_num;
}event_data;

int write_send (event_data ev) {
    if(write_shm(ev.addr, &(ev.data), sizeof(char)) == SHM_ERROR) {
        LOG_ERROR("can't write [%s] data to [%d]", ev.name, ev.addr);
        return INPUT_ERROR;
    }

    LOG_INFO("write [%s] data to shared memory", ev.name);

    send_signal(ev.pid, ev.sig_num);
    LOG_INFO("send signal#[%d] to [%d] process", ev.sig_num, ev.pid);

    return INPUT_SUCCESS;
}

int send_read_key (pid_t pid, char key_code) {
    event_data ev = {"read_key", SHM_ADDR_RK, key_code, pid, SIGUSR1};
    return write_send(ev);
}

int send_switch_button (pid_t pid, char button_num) {
    event_data ev = {"switch_button", SHM_ADDR_BUTT, button_num, pid, SIGUSR2};
    return write_send(ev);
}