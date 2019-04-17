//
// Created by 민지우 on 2019-04-16.
//
#include <string.h>
#include "editor.h"

#include "../../services/log/log.h"

#include "../../controllers/device/client/device_client.h"
#include "../../controllers/input/receiver/receiver.h"

#include "../../devices/lcd/lcd_itf.h"
#include "../../devices/switch/switch_itf.h"
#include "../../devices/fnd/fnd_itf.h"


#define CNT_BUTTON  9
#define CNT_BUTTON_MODE 4

#define EDITOR_ALPHA    0
#define EDITOR_NUM      1

#define EDITOR_SUCESS   1
#define EDITOR_ERROR    -1

#define MAX_CNT         9999


int edit_text1();
int edit_text2();
int edit_text3();
int edit_text4();
int edit_text5();
int edit_text6();
int edit_text7();
int edit_text8();
int edit_text9();
int edit_text10();
static int start_mode_alpha();
static int start_mode_num ();


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
unsigned char dot_alpha_a[10] = {0x1c,0x36,0x63,0x63,0x63,0x7f,0x7f,0x63,0x63,0x63};
unsigned char dot_num_1[10] = {0x0c,0x1c,0x1c,0x0c,0x0c,0x0c,0x0c,0x0c,0x0c,0x1e};
static unsigned int MODE = EDITOR_ALPHA;

static unsigned int prev_btn = -1;
static unsigned int prev_count = 0;

static unsigned char total_count = 0;
static unsigned char text[LCD_MAX_BUFF + 1] = "";


int print_text() {
    LOG_INFO("EDITOR:: print [%s]", text);
    return print_lcd(text);
}

char get_char(int sw) {
    if (sw == SW12) return ' ';
    if (MODE == EDITOR_NUM) return sw + '0';

    if (sw == prev_btn) {
        prev_count++;
        prev_count %= CNT_BUTTON_MODE;
    } else {
        prev_count = 0;
        prev_btn = -1;
    }
    return map_alpha[sw][prev_count];
}

int inc_cnt () {
    unsigned char tmp[FND_MAX_DIGIT];
    int r;
    int q = 1;
    int i = 0;
    total_count++;
    total_count %= MAX_CNT;

    for (i = 0; i < FND_MAX_DIGIT - 1; i++, q *= 10);

    for (i = 0, r = total_count; i < FND_MAX_DIGIT; i++) {
        tmp[i] = r / q;
        r %= q;
    }

    return print_fnd(tmp);
}

int edit_text (int sw) {
    int len = strlen((const char *)text);
    char c;
    unsigned char temp[LCD_MAX_BUFF];

    if (sw == prev_btn) text[len - 1] = '\0';

    if (len == LCD_MAX_BUFF) {
        strncpy((char *)temp, (char *)(text + 1), len - 1);
        strncpy((char*)text, (char*)temp, len - 1);
    }

    c = get_char(sw);
    strncat((char*)text, &c, 1);
    LOG_INFO("EDITOR:: Success to add [%c]", c);

    print_text();
    inc_cnt();
    return EDITOR_SUCESS;
}

int reset_text () {
    text[0] = '\0';
    total_count = 0;
    print_fnd(&total_count);

    LOG_INFO("EDITOR:: Success to reset text");

    return SWITCH_SUCCESS;
}

int change_editor_mode () {
    if (MODE == EDITOR_ALPHA) start_mode_alpha();
    else start_mode_num();

    LOG_INFO("EDITOR:: Success to change mode to [%d]", MODE);
    return EDITOR_SUCESS;
}

int start_mode_alpha() {
    MODE = EDITOR_ALPHA;
    prev_count = 0;
    prev_btn = -1;

    dot_print(dot_alpha_a);

    LOG_INFO("EDITOR:: Start alphabet mode");
    return EDITOR_SUCESS;
}

int start_mode_num () {
    MODE = EDITOR_NUM;
    prev_count = 0;
    prev_btn = -1;

    dot_print(dot_num_1);
    LOG_INFO("EDITOR:: Start number mode");
    return EDITOR_SUCESS;
}


int editor_init() {

    reset_text();
    start_mode_alpha();


    add_sw_handler(SW1, edit_text1);
    add_sw_handler(SW2, edit_text2);
    add_sw_handler(SW3, edit_text3);
    add_sw_handler(SW4, edit_text4);
    add_sw_handler(SW5, edit_text5);
    add_sw_handler(SW6, edit_text6);
    add_sw_handler(SW7, edit_text7);
    add_sw_handler(SW8, edit_text8);
    add_sw_handler(SW9, edit_text9);
    add_sw_handler(SW10, reset_text);
    add_sw_handler(SW11, change_editor_mode);
    add_sw_handler(SW12, edit_text10);

    LOG_INFO("EDITOR:: Success to init");
    return EDITOR_SUCESS;
}

int editor_exit() {
    text[0] = '\0';
    total_count = 0;

    remove_sw_handler();

    LOG_INFO("EDITOR:: Success to exit");
    return EDITOR_SUCESS;
}







int edit_text1() {
    return edit_text(SW1);
}

int edit_text2() {
    return edit_text(SW2);
}

int edit_text3() {
    return edit_text(SW3);
}

int edit_text4() {
    return edit_text(SW4);
}

int edit_text5() {
    return edit_text(SW5);
}

int edit_text6() {
    return edit_text(SW6);
}

int edit_text7() {
    return edit_text(SW7);
}

int edit_text8() {
    return edit_text(SW8);
}

int edit_text9() {
    return edit_text(SW9);
}

int edit_text10() {
    return edit_text(SW10);
}

