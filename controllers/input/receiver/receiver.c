//
// Created by 민지우 on 2019-04-13.
//

#include "receiver.h"
#include "../input_itf.h"
#include "../../../services/shared_memory/shared_memory.h"

int get_rk_code () {
    char code = *(get_shm_addr() + SHM_ADDR_RK);
    return (int) code;
}

int get_switch_button () {
    char button = *(get_shm_addr() + SHM_ADDR_BUTT);
    return (int) button;
}