//
// Created by 민지우 on 2019-04-11.
//

#include <stdlib.h>

#include "../../../services/mq/mq.h"
#include "dot.h"
#include "../itf.h"
#include "../../../devices/dot/dot_itf.h"
#include "../../../services/log/log.h"

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