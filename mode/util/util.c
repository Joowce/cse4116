//
// Created by 민지우 on 2019-04-17.
//

#include "util.h"
#include "../../devices/fnd/fnd_itf.h"
#include "../../controllers/device/client/device_client.h"

#define MAX_CNT 9999

static int total_count = 0;


int print_cnt () {
    unsigned char tmp[FND_MAX_DIGIT];
    int r;
    int q = 1;
    int i = 0;
    for (i = 0; i < FND_MAX_DIGIT - 1; i++, q *= 10);

    for (i = 0, r = total_count; i < FND_MAX_DIGIT; i++, r %= q, q /= 10) {
        tmp[i] = r / q;
    }
    return print_fnd(tmp);
}

int init_cnt () {
    total_count = 0;
    return print_cnt();
}


int inc_cnt () {
    total_count++;
    total_count %= MAX_CNT;
    return print_cnt();
}