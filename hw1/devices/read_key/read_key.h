//
// Created by 민지우 on 2019-04-12.
//

#ifndef EMBEDED_READ_KEY_H
#define EMBEDED_READ_KEY_H


#define RK_ERROR    -1
#define RK_SUCCESS  1


#define RK_CODE_BACK        158
#define RK_CODE_VOL_UP      115
#define RK_CODE_VOL_DOWN    114

int open_rk ();
int close_rk ();
int get_pressed_rk ();

#endif //EMBEDED_READ_KEY_H
