//
// Created by 민지우 on 2019-04-10.
//

#ifndef EMBEDED_MQ_H
#define EMBEDED_MQ_H

#define MESSAGE_SIZE    124


typedef struct {
    int device_type;
    int callback_num;
    int arg_cnt;
    unsigned char data[MESSAGE_SIZE];
} MESSAGE;

MESSAGE* get_message ();
int send_message (MESSAGE);

#endif //EMBEDED_MQ_H
