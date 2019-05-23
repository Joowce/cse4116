//
// Created by 민지우 on 2019-04-10.
//

#ifndef EMBEDED_MQ_H
#define EMBEDED_MQ_H

#define MESSAGE_SIZE    124
#define MESSAGE_KEY     961026

#define MQ_ERROR       -1
#define MQ_SUCCESS      1

typedef struct {
    int device_type;
    int callback_num;
    int arg_cnt;
    unsigned char data[MESSAGE_SIZE];
} MESSAGE;

typedef struct {
    long mtype;
    MESSAGE data;
} msgbuf;


int create_message_queue ();
int remove_message_queue ();

msgbuf* create_message(int device_type, int callback_num, int cnt, unsigned char* data);
int get_message (msgbuf *);
int send_message (msgbuf *);

#endif //EMBEDED_MQ_H
