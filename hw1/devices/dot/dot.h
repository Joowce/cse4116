//
// Created by 민지우 on 2019-04-11.
//
#include "../../services/callback.h"
#include "./dot_itf.h"

#ifndef EMBEDED_DOT_H
#define EMBEDED_DOT_H

int open_dot ();
int close_dot ();

int cb_print_dot (int num, ...);
int cb_print_dot_num(int num, ...);

callback get_callback_dot (int num_cb);

#define OPEN_DOT        open_dot
#define CLOSE_DOT       close_dot

#define DOT_SIZE        10

extern const callback DOT_CALLBACK[NUM_CALLBACK_DOT];

#endif //EMBEDED_DOT_H
