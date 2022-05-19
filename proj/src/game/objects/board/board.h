#ifndef _LCOM_BOARD_H_
#define _LCOM_BOARD_H_

#include "../pieces/pieces.h"

#define BOARD_SIZE 8
extern board* table;
typedef struct Piece board[BOARD_SIZE][BOARD_SIZE];
Color get_square_color(uint8_t lin, uint8_t col); //returns the color of the square in lin/col
#endif