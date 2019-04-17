//
// Created by 민지우 on 2019-04-12.
//

#include <stdlib.h>

#include "device_client.h"

#include "../../../services/mq/mq.h"
#include "../../../services/log/log.h"

#include "../itf.h"
#include "../../../devices/fnd/fnd_itf.h"
#include "../../../devices/led/led_itf.h"
#include "../../../devices/lcd/lcd_itf.h"
#include "../../../devices/dot/dot_itf.h"

#include "../../../devices/led/light.h"
#include "../../../devices/dot/font/font.h"


/**
 * fnd print data
 * @param data: should be character array with number
 * @return
 */
int print_fnd (unsigned char * data) {
    msgbuf *buf = create_message(DEVICE_FND, PRINT_FND, 1, data);
    int result = send_message(buf);
    if (result == MQ_ERROR) {
        LOG_ERROR("Fail:: print fnd: can't send message");
    }
    free(buf);
    return result;
}

/**
 * light led
 * @param val: # of light that shoud be light
 * @return
 */
int light_led (unsigned char val) {
    msgbuf *buf = create_message(DEVICE_LED, LIGHT_LED, 1, &val);
    int result = send_message(buf);
    if (result == MQ_ERROR) {
        LOG_ERROR("Fail:: print dot: can't send message");
    }
    free(buf);

    return result;
}

/**
 * print lcd
 * @param string: that will be printed
 * @return
 */
int print_lcd (unsigned char* string) {
    msgbuf *buf = create_message(DEVICE_LCD, PRINT_LCD, 1, string);
    int result = send_message(buf);
    if (result == MQ_ERROR) {
        LOG_ERROR("Fail:: print dot: can't send message");
    }
    free(buf);

    return result;
}


/**
 * dot matrix print
 * @param data : dot matrix data array
 * @return result: -1::ERROR 1::SUCCESS
 */
int dot_print(unsigned char * data) {
    msgbuf *buf = create_message(DEVICE_DOT, DOT_PRINT, 1, data);
    int result = send_message(buf);
    if (result == MQ_ERROR) {
        LOG_ERROR("Fail:: print dot: can't send message");
    }
    free(buf);

    return result;
}

/**
 * dot matrix print number
 * @param num: number that is drawn
 * @return result: -1::ERROR 1::SUCCESS
 */
int dot_print_num (int num) {
    msgbuf *buf = create_message(DEVICE_DOT, DOT_PRINT_NUM, 1, (unsigned  char *)&num);
    int result = send_message (buf);
    if (result == MQ_ERROR) {
        LOG_ERROR("Fail:: print dot num: can't send message");
    }
    free(buf);

    return result;
}

int dvice_init () {
    unsigned char init_fnd_val[FND_MAX_DIGIT] = {0,};
    unsigned char init_lcd_val[LCD_MAX_BUFF] = {0,};

    dot_print(dot_set_blank);
    print_fnd(init_fnd_val);
    print_lcd(init_lcd_val);
    light_led(LED_OFF);

    LOG_INFO("CTRL_client:: Success to initialize devices");
    return 1;
}