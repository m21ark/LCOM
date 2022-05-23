#ifndef _LCOM_VIEW_H_
#define _LCOM_VIEW_H_

#include "../../drivers/graph/video_graphic.h"
#include "../objects/board/board.h"
#include "../objects/pieces/pieces.h"
#include "../sprite/sprite.h"
#include <lcom/lcf.h>

#define BOARD_START_POS_X 0
#define BOARD_START_POS_Y 0

#define BOARD_SCREEN_CASE_SIZE 94
#define BOARD_SCREEN_SIZE 800

#define BOARD_NUMBER_OF_CASES 64
#define BOARD_NUMBER_OF_COL 8
#define BOARD_NUMBER_OF_LIN 8

#define BOARD_BLACK_CASE_COLOR 0x769656
#define BOARD_WHITE_CASE_COLOR 0xeeeed2

static bool moves[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0, 0}};

void draw_board();
void draw_pieces(Board table[8][8]);
void draw_piece(Board piece, unsigned int x, unsigned int y);
void draw_clock();

void get_selected_valid_moves(bool arr[8][8]);

#endif
