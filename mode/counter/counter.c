//
// Created by 민지우 on 2019-04-16.
//
#include "counter.h"

#include "../../services/log/log.h"

#include "../../controllers/device/client/device_client.h"
#include "../../controllers/input/receiver/receiver.h"

#include "../../devices/led/light.h"

#define NUM_NS  4
#define DIGIT   3

typedef struct {
    int number;
    int upper_boundary;
    int lowe_boundary;
    int light;
}number_system;

static void convert_num_str (number_system ns, int num, unsigned char* num_str);
static int draw_number ();
static int inc_num_digit(int num, number_system ns, int digit);
static int start_num_system();

static int cnt = 0;
int idx_ns = 0;
static number_system NS[NUM_NS]= {
        {10, 1000, 0, LED_2},
        {8, 512, 0, LED_3},
        {4, 64, 0, LED_4},
        {2, 8, 0, LED_1}
};


int rotate_num_system() {
    idx_ns++;
    idx_ns %= NUM_NS;

    start_num_system();
    draw_number();
    return 1;
}

int inc_digit0() {
    cnt = inc_num_digit(cnt, NS[idx_ns], 0);
    return draw_number();
}

int inc_digit1() {
    cnt = inc_num_digit(cnt, NS[idx_ns], 1);
    return draw_number();
}

int inc_digit2() {
    cnt = inc_num_digit(cnt, NS[idx_ns], 2);
    return draw_number();
}

int counter_init() {
    cnt = 0;
    idx_ns = 0;

    add_sw_handler(SW1, rotate_num_system);
    add_sw_handler(SW2, inc_digit2);
    add_sw_handler(SW3, inc_digit1);
    add_sw_handler(SW4, inc_digit0);

    start_num_system();
    draw_number();

    LOG_INFO("counter:: Success to initialize");
    return 1;
}

int counter_exit() {
    cnt = 0;
    idx_ns = 0;

    remove_sw_handler();
    LOG_INFO("counter:: Success to exit counter mode");
    return 1;
}

void convert_num_str (number_system ns, int num, unsigned char* num_str) {
    int i;
    int q = num;
    for (i = DIGIT - 1; i >= 0; i--) {
        num_str[i] = (char)((q % ns.number) + '0');
        q = q / ns.number;
    }
    LOG_INFO("counter:: convert:: NS:[%d]: [%d] to [%s]", ns.number, num, num_str);
}

int draw_number () {
    unsigned char num_str[DIGIT] = {0,};
    convert_num_str(NS[idx_ns], cnt, num_str);

    print_fnd(num_str);
    LOG_INFO("counter:: print %s", num_str);
    return 1;
}

int inc_num_digit(int num, number_system ns, int digit) {
    int tmp = 1;
    for (int i = 0; i < digit; i++, tmp *= ns.number);
    num += tmp;
    num %= ns.upper_boundary;

    LOG_INFO("counter:: increment number_system[%d], digit[%d]:: result: [%d]", ns.number, digit, num);

    return num;
}

int start_num_system() {
    cnt %= NS[idx_ns].upper_boundary;
    light_led(NS[idx_ns].light);

    LOG_INFO("counter:: start [%d] number system", NS[idx_ns].number);

    return 1;
}




