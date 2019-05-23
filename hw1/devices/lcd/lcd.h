//
// Created by 민지우 on 2019-04-12.
//
#include "./lcd_itf.h"
#include "../../services/callback.h"

#ifndef EMBEDED_LCD_H
#define EMBEDED_LCD_H

int open_lcd();
int close_lcd ();
int cb_print_lcd (int, ...);


#define OPEN_LCD    open_lcd
#define CLOSE_LCD   close_lcd

extern const callback LCD_CALLBACK[NUM_CALLBACK_LCD];

#endif //EMBEDED_LCD_H
