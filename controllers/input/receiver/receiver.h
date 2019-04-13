//
// Created by 민지우 on 2019-04-13.
//

#include "../../../services/callback.h"
#include "../../../devices/switch/switch_itf.h"

#ifndef EMBEDED_RECEIVER_H
#define EMBEDED_RECEIVER_H

int init_rk_sig ();
int init_sw_sig ();

int add_rk_handler(int, callback_no_arg);
int add_sw_handler(int, callback_no_arg);

int remove_sw_handler();
int remove_rk_handler();

#define RECEIVER_ERROR      -1
#define RECEIVER_SUCCESS    1

#endif //EMBEDED_RECEIVER_H
