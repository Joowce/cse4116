//
// Created by 민지우 on 2019-04-16.
//

#include "counter.h"

#include "../../services/log/log.h"

#include "../../controllers/device/client/device_client.h"

#define NUM_NS  4
#define DIGIT   3

typedef struct {
    int number;
    int max;
    int min;
}number_system;

static int cnt = 0;
static number_system NS[NUM_NS]= {{10, 999, 0}, {8, 511, 0}, {4, 63, 0}, {2, 7, 0}};
int idx_ns = 0;

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
}

