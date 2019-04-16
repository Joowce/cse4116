//
// Created by 민지우 on 2019-04-16.
//

#include "editor.h"

//#include "../../"


#define CNT_BUTTON  9
#define CNT_BUTTON_MODE 4

#define EDITOR_ALPHA    0
#define EDITOR_NUM      1

static unsigned char map_alpha[CNT_BUTTON][CNT_BUTTON_MODE] = {
        {'Z', '.', 'Q', '1'},
        {'C', 'A', 'B', '2'},
        {'F', 'D', 'E', '3'},
        {'I', 'G', 'H', '4'},
        {'L', 'J', 'K', '5'},
        {'O', 'M', 'N', '6'},
        {'S', 'P', 'R', '7'},
        {'V', 'T', 'U', '8'},
        {'Y', 'W', 'X', '9'}
};
static unsigned int MODE = EDITOR_ALPHA;

static unsigned int prev_btn = -1;
static unsigned int prev_count = 0;

static unsigned int total_count = 0;

