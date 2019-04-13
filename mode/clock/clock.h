//
// Created by 민지우 on 2019-04-13.
//

#ifndef EMBEDED_CLOCK_H
#define EMBEDED_CLOCK_H

#define CLOCK_BASE_MODE     0
#define CLOCK_CHANGE_MODE   1
#define CLOCK_OFF           -1

int clock_init();
int clock_execute();
int clock_exit();

#endif //EMBEDED_CLOCK_H
