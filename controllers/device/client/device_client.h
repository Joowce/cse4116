//
// Created by 민지우 on 2019-04-12.
//

#ifndef EMBEDED_DEVICE_CLIENT_H
#define EMBEDED_DEVICE_CLIENT_H


/**
 * FND
 */
int print_fnd (unsigned char*);

/**
 * Led
 */
int light_led (unsigned char);

/**
 * Lcd
 */
int print_lcd (unsigned char*);

/**
 * Dot matrix
 */
int dot_print(unsigned char*);
int dot_print_num (int num);

#endif //EMBEDED_DEVICE_CLIENT_H
