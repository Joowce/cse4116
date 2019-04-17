//
// Created by 민지우 on 2019-04-17.
//

#include "board.h"

#include "../util/util.h"

#include "../../services/timer/timer.h"
#include "../../services/log/log.h"

#include "../../controllers/device/client/device_client.h"
#include "../../controllers/input/receiver/receiver.h"

#define BOARD_SUCCESS   1
#define BOARD_ERROR     -1
#define MAX_ROW         10
#define MAX_COL         7
#define CUR_SHOW        1
#define CUR_HIDE        0
#define ONE_SEC         1

int inc_row ();
int dec_row ();
int inc_col ();
int dec_col ();

int print_board();
int get_board_status (int r, int c);

int fill_dot (int r, int c);
int reset_dot(int r, int c);
int change_dot(int r, int c);

int hide_cur();
int show_cur();

static unsigned char board[MAX_ROW]={0};
static int cur_r = 0;
static int cur_c = 0;
static char cur_val = 0;
static char cur_status = CUR_SHOW;


void blink (int signo) {
    if (cur_status == CUR_HIDE) return;
    change_dot(cur_r, cur_c);
    print_board();
}

int fill_cur_val () {
    inc_cnt();
    fill_dot(cur_r, cur_c);
    return print_board();
}

int restore_cur () {
    if (cur_val == BOARD_ERROR) reset_dot(cur_r, cur_c);
    else fill_dot(cur_r, cur_r);
    LOG_INFO("BOARD:: Success to restore board[%d][%d]: [%d]", cur_r, cur_c, cur_val);
    return BOARD_SUCCESS;
}

int store_cur(int r, int c) {
    cur_val = get_board_status(r, c);
    LOG_INFO("BOARD:: Success to store board[%d][%d]: [%d]", r, c, cur_val);
    return BOARD_SUCCESS;
}

int clear_board() {
    int i;
    for (i=0; i < MAX_ROW; i++) {
        board[i] = 0;
    }
    return print_board();
}

int reset_board() {
    cur_r = 0;
    cur_c = 0;
    clear_board();
    show_cur();
    return print_board();
}

int change_cur_status() {
    inc_cnt();
    if (cur_status == CUR_SHOW) return hide_cur();
    return show_cur();
}

int reverse_board() {
    unsigned char mask = 1 << MAX_COL;
    mask--;
    cur_val = cur_val == BOARD_SUCCESS ? BOARD_ERROR : BOARD_SUCCESS;
    for (int i = 0; i < MAX_ROW; i++) {
        board[i] = ~board[i];
        board[i] &= mask;
    }
    inc_cnt();
    print_board();
    LOG_INFO("BOARD:: Success to reverse board");
    return BOARD_SUCCESS;
}

int clear_board_sw() {
    clear_board();
    return inc_cnt();
}
int reset_board_sw() {
    reset_board();
    return inc_cnt();
}

int board_init() {
    reset_board();
    init_cnt();

    add_sw_handler(SW1, reset_board_sw);
    add_sw_handler(SW2, dec_row);
    add_sw_handler(SW3, change_cur_status);
    add_sw_handler(SW4, dec_col);
    add_sw_handler(SW5, fill_cur_val);
    add_sw_handler(SW6, inc_col);
    add_sw_handler(SW7, clear_board_sw);
    add_sw_handler(SW8, inc_row);
    add_sw_handler(SW9, reverse_board);

    LOG_INFO("BOARD:: Success to init board");
    return BOARD_SUCCESS;
}


int board_exit() {
    reset_board();
    timer_cancel();

    remove_sw_handler();
    return BOARD_SUCCESS;
}

int inc_row () {
    int temp;
    restore_cur();

    temp = (cur_r + 1) % MAX_ROW;
    store_cur(temp, cur_c);
    cur_r = temp;
    inc_cnt();
    return print_board();
}

int dec_row() {
    int temp;
    restore_cur();

    temp = (cur_r - 1 + MAX_ROW) % MAX_ROW;
    store_cur(temp, cur_c);
    cur_r = temp;
    inc_cnt();
    return print_board();
}

int inc_col () {
    int temp;
    restore_cur();

    temp = (cur_c + 1) % MAX_COL;
    store_cur(cur_r, temp);
    cur_c = temp;
    inc_cnt();
    return print_board();
}

int dec_col () {
    int temp;
    restore_cur();

    temp = (cur_c - 1 + MAX_COL) % MAX_COL;
    store_cur(cur_r, temp);
    cur_c = temp;
    inc_cnt();
    return print_board();
}


int fill_dot (int r, int c) {
    unsigned char mask = 1 << (MAX_COL - c - 1);
    board[r] |= mask;
    return BOARD_SUCCESS;
}

int reset_dot(int r, int c) {
    unsigned char mask = 1 << (MAX_COL - c - 1);
    mask = ~mask;
    board[r] &= mask;
    return BOARD_SUCCESS;
}

int change_dot(int r, int c) {
    if (get_board_status(r, c) == BOARD_ERROR) fill_dot(r, c);
    else reset_dot(r, c);
    return BOARD_SUCCESS;
}

int get_board_status (int r, int c) {
    unsigned char mask = 1 << (MAX_COL - c - 1);
    return (board[r] & mask) > 1 ? BOARD_SUCCESS : BOARD_ERROR;
}

int print_board() {
    return dot_print(board);
}


int hide_cur() {
    cur_status = CUR_HIDE;
    timer_cancel();
    return restore_cur();
}

int show_cur () {
    cur_status = CUR_SHOW;
    store_cur(cur_r, cur_c);
    timer_start(blink, ONE_SEC);
    return BOARD_SUCCESS;
}