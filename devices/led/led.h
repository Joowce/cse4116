//
// Created by 민지우 on 2019-04-12.
//
#include "../../services/callback.h"
#include "./led_itf.h"

#ifndef EMBEDED_LED_H
#define EMBEDED_LED_H

int open_led();
int close_led ();
int cb_light_led (int, ...);

#define OPEN_LED    open_led
#define CLOSE_LED   close_led

extern callback LED_CALLBACK[NUM_CALLBACK_LED];

#endif //EMBEDED_LED_H
