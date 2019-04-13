//
// Created by 민지우 on 2019-04-13.
//
#include <time.h>

#include "clock.h"
#include "../../services/log/log.h"
#include "../../services/timer/timer.h"

#include "../../controllers/device/client/device_client.h"
#include "../../controllers/input/receiver/receiver.h"

#include "../../devices/led/light.h"

#define ONE_SEC 1000


static int hour, minutes;
static int tmp_hour, tmp_minutes;
static int CLOCK_MODE = CLOCK_OFF;
static int prev_led = LED_4;

int draw_time(int h, int m) {
    unsigned char time[4] = {(char)(h / 10), (char)(h % 10), (char)(m / 10), (char)(m % 10)};
    return print_fnd(time);
}

int add_hour (int *h) {
    (*h)++;
    (*h)%= 24;
    return 1;
}

int add_minutes (int* h, int *m) {
    (*m)++;
    if (*m == 60) {
        add_hour(h);
        (*m) = 0;
    }
    return 1;
}

int add_hour_change () {
    return add_hour(&tmp_hour);
}

int add_minutes_change () {
    return add_minutes(&tmp_hour, &tmp_minutes);
}

int reset_clock_change () {
    if (CLOCK_MODE != CLOCK_CHANGE_MODE) return 1;
    tmp_hour = hour;
    tmp_minutes = minutes;

    return 1;
}


void light_in_turn (int signo) {
    if (CLOCK_MODE != CLOCK_CHANGE_MODE) return;
    prev_led = prev_led == LED_3 ? LED_4 : LED_3;
    light_led(prev_led);

    start_timer(light_in_turn, ONE_SEC);
}

void run_clock(int signo) {
    if(CLOCK_MODE != CLOCK_BASE_MODE) return;
    add_minutes(&hour, &minutes);

    start_timer(run_clock, ONE_SEC);
}

int start_change_mode () {
    if (CLOCK_MODE == CLOCK_CHANGE_MODE) return 1;
    CLOCK_MODE = CLOCK_CHANGE_MODE;

    light_in_turn(0);
    reset_clock_change();
    LOG_INFO("CLOCK:: change_mode");
    return 1;
}


int save_change_mode () {
    if (CLOCK_MODE == CLOCK_BASE_MODE) return 1;
    CLOCK_MODE = CLOCK_BASE_MODE;

    hour = tmp_hour;
    minutes = tmp_minutes - 1;

    run_clock(0);
    LOG_INFO("CLOCK:: return to base mode");
    return 1;
}

int switch_mode () {
    if(CLOCK_MODE == CLOCK_BASE_MODE) start_change_mode();
    else if (CLOCK_MODE == CLOCK_CHANGE_MODE) save_change_mode();
}


int clock_execute_change_mode () {
    return draw_time(tmp_hour, tmp_minutes);
}

int clock_execute_base () {
    light_led(LED_1);
    draw_time(hour, minutes);
    return 1;
}

int clock_execute () {
    if (CLOCK_MODE == CLOCK_BASE_MODE) clock_execute_base();
    else if(CLOCK_MODE == CLOCK_CHANGE_MODE) clock_execute_change_mode();
    return 1;
}

int clock_init () {
    time_t cur_time = time(NULL);
    struct tm *cur_tm = localtime(&cur_time);

    hour = cur_tm -> tm_hour;
    minutes = cur_tm -> tm_min - 1;

    CLOCK_MODE = CLOCK_BASE_MODE;
    run_clock(0);

//  add handler
    add_sw_handler(SW1, switch_mode);
    add_sw_handler(SW2, reset_clock_change);
    add_sw_handler(SW3, add_hour_change);
    add_sw_handler(SW4, add_minutes_change);

    return 1;
}


int clock_exit() {
    remove_sw_handler();
    CLOCK_MODE = CLOCK_OFF;
    return 1;
}