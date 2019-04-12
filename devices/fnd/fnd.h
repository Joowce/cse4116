//
// Created by 민지우 on 2019-04-12.
//

#include "../../services/callback.h"
#include "fnd_itf.h"

#ifndef EMBEDED_FND_H
#define EMBEDED_FND_H

int open_fnd();
int close_fnd ();
int cb_print_fnd (int, ...);


#define OPEN_FND    open_fnd
#define CLOSE_FND   close_fnd

extern const callback FND_CALLBACK[NUM_CALLBACK_FND];


#endif //EMBEDED_FND_H
