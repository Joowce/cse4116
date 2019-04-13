//
// Created by 민지우 on 2019-04-12.
//

#include <stdlib.h>

#ifndef EMBEDED_INPUT_H
#define EMBEDED_INPUT_H

#define INPUT_ERROR     -1
#define INPUT_SUCCESS   1

int send_switch_button (pid_t pid, char button_num);
int send_read_key (pid_t pid, char key_code);

#endif //EMBEDED_INPUT_H
