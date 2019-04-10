//
// Created by 민지우 on 2019-04-11.
//
#include "../../services/callback.h"

#ifndef EMBEDED_DOT_H
#define EMBEDED_DOT_H

int open_dot ();
int close_dot ();

int cb_print_dot (int num, ...);
int cb_print_dot_num(int num, ...);

#define DOT_PRINT           0
#define DOT_PRINT_NUM       1

#define NUM_CALLBACK_DOT    2

const callback DOT_CALLBACK[NUM_CALLBACK_DOT] = {cb_print_dot, cb_print_dot_num};

#define OPEN_DOT        open_dot
#define CLOSE_DOT       close_dot

#endif //EMBEDED_DOT_H
