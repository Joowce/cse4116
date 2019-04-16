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

// device interface
static int draw_time(int h, int m);
void light_in_turn (int signo);

// change hour
static int inc_hour_change();
static int inc_minutes_change();
static int inc_hour(int *h);
static int inc_minutes(int *h, int *m);

// for change mode
static int reset_clock_change();
static int start_change_mode ();
static int save_change_mode ();

void run_clock(int signo);

/* global data */
static int hour, minutes;
static int tmp_hour, tmp_minutes;
static int CLOCK_MODE = CLOCK_OFF;
static int prev_led = LED_4;


int switch_mode () {
    LOG_INFO("clock:: change mode");
    if(CLOCK_MODE == CLOCK_BASE_MODE) start_change_mode();
    else if (CLOCK_MODE == CLOCK_CHANGE_MODE) save_change_mode();
}

void start_base_mode() {
    if (CLOCK_MODE == CLOCK_BASE_MODE) return;

    LOG_INFO("clock:: start base mode");
    CLOCK_MODE = CLOCK_BASE_MODE;

    minutes--;

    light_led(LED_1);
    run_clock(0);
}

int clock_init () {
    time_t cur_time = time(NULL);
    struct tm *cur_tm = localtime(&cur_time);

    hour = cur_tm -> tm_hour;
    minutes = cur_tm -> tm_min;

    start_base_mode();

//  add handler
    add_sw_handler(SW1, switch_mode);
    add_sw_handler(SW2, reset_clock_change);
    add_sw_handler(SW3, inc_hour_change);
    add_sw_handler(SW4, inc_minutes_change);

    LOG_INFO("clock:: success to initialize clock");

    return 1;
}


int clock_exit() {
    remove_sw_handler();
    CLOCK_MODE = CLOCK_OFF;

    LOG_INFO("clock:: success to exit clock");

    return 1;
}


/**
 * draw hour, minutes to FND
 * @param h : hour
 * @param m : minutes
 * @return
 */
int draw_time(int h, int m) {
    unsigned char time[4] = {(char)(h / 10), (char)(h % 10), (char)(m / 10), (char)(m % 10)};
    return print_fnd(time);
}

/**
 * light LED3 and 4 in turn
 * @param signo
 */
void light_in_turn (int signo) {
    if (CLOCK_MODE != CLOCK_CHANGE_MODE) return;
    prev_led = prev_led == LED_3 ? LED_4 : LED_3;
    light_led(prev_led);

    start_timer(light_in_turn, ONE_SEC);
}

/**
 * increment hour
 * @param h
 * @return
 */
int inc_hour (int *h) {
    (*h)++;
    (*h) %= 24;
    return 1;
}

/**
 * increment minutes
 * @param h
 * @param m
 * @return
 */
int inc_minutes (int* h, int *m) {
    (*m)++;
    if (*m == 60) {
        inc_hour(h);
        (*m) = 0;
    }
    return 1;
}

/**
 * increment change hour
 * @return
 */
int inc_hour_change () {
    inc_hour(&tmp_hour);
    draw_time(tmp_hour, tmp_minutes);

    LOG_INFO("clock:: increment hour to [%02d]", tmp_hour);

    return 1;
}

/**
 * increment change minute
 * @return
 */
int inc_minutes_change () {
    inc_minutes(&tmp_hour, &tmp_minutes);
    draw_time(tmp_hour, tmp_minutes);

    LOG_INFO("clock:: increment minutes to [%02d]", tmp_minutes);

    return 1;
}

int reset_clock_change () {
    if (CLOCK_MODE != CLOCK_CHANGE_MODE) return 1;
    tmp_hour = hour;
    tmp_minutes = minutes;

    LOG_INFO("clock:: Success to reset clock_change");
    return 1;
}

int start_change_mode () {
    if (CLOCK_MODE == CLOCK_CHANGE_MODE) return 1;
    CLOCK_MODE = CLOCK_CHANGE_MODE;

    light_in_turn(0);
    reset_clock_change();
    draw_time(tmp_hour, tmp_minutes);
    LOG_INFO("CLOCK:: Success to start change mode");
    return 1;
}


int save_change_mode () {
    if (CLOCK_MODE == CLOCK_BASE_MODE) return 1;
    hour = tmp_hour;
    minutes = tmp_minutes;

    start_base_mode();
    LOG_INFO("CLOCK:: return to base mode");
    return 1;
}

void run_clock(int signo) {
    if(CLOCK_MODE != CLOCK_BASE_MODE) return;

    LOG_INFO("clock:: run clock [%02d:%02d]", hour, minutes);
    inc_minutes(&hour, &minutes);
    draw_time(hour, minutes);

    start_timer(run_clock, ONE_SEC);
}

