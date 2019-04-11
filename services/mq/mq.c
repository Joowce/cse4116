//
// Created by 민지우 on 2019-04-10.
//
#include <stdlib.h>
#include <memory.h>
#include <sys/msg.h>

#include "mq.h"
#include "../../devices/dot/dot.h"
#include "../../services/log/log.h"

static int MQ_ID = -1;

/**
 * 메세지 큐 생성
 * @return 생성 성공 여부
 */
int create_message_queue () {
    if (MQ_ID != -1) return MQ_ID;

    MQ_ID = msgget((key_t)MESSAGE_KEY,  IPC_CREAT|0666);

    if (MQ_ID == MQ_ERROR) LOG_ERROR("Fail:: create MQ");
    else LOG_INFO("Success:: create MQ");

    return MQ_ID == MQ_ERROR ? MQ_ERROR : MQ_SUCCESS;
}

/**
 * 메세지를 생성
 * @param device_type: target device #
 * @param callback_num: target callback #
 * @param data: arguments of callback func
 * @return address of msgbuf
 */
msgbuf* create_message(int device_type, int callback_num, int cnt, unsigned char* data) {
    msgbuf* msg = (msgbuf *) malloc(sizeof(msgbuf));

    msg->mtype = 1;

    msg->data.device_type = device_type;
    msg->data.callback_num = callback_num;
    msg->data.arg_cnt = cnt;
    if (data != NULL) memcpy(msg->data.data, data, sizeof(msg->data.data));
    return msg;
}

/**
 * message queue에 있는 message를 msg에 옮기는 함수
 * @param msg
 * @return
 */
int get_message (msgbuf * msg) {
    int sz;

    if (MQ_ID == MQ_ERROR) {
        LOG_ERROR("No Message queue");
        return MQ_ERROR;
    }

    sz = msgrcv(MQ_ID, msg, sizeof(msgbuf), 0, 0);
    if (sz == -1) {
        LOG_ERROR("Fail to get message");
        return MQ_ERROR;
    }

    LOG_INFO("Success to get message:: size: %d", sz);
    return MQ_SUCCESS;
}


int send_message (msgbuf* msg) {
    int sz;

    if (MQ_ID == MQ_ERROR) {
        LOG_ERROR("No Message queue");
        return MQ_ERROR;
    }

    sz = msgsnd(MQ_ID,(void *)msg, sizeof(MESSAGE), 0);

    if(sz == -1) {
        LOG_ERROR("Fail to send message");
        return MQ_ERROR;
    }

    LOG_INFO("Success to send message");
    return MQ_SUCCESS;
}

int remove_message_queue () {
    return msgctl(MQ_ID, IPC_RMID, NULL);
}