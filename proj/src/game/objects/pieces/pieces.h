#ifndef _LCOM_PIECES_H_
#define _LCOM_PIECES_H_

#include <lcom/lcf.h>
#include "../board/board.h"

#define LINE(n) (0xFF<<(8 * (7-n))) //uint64_t com a Linha n do tabuleiro
#define COLUMN(n) (BIT(63-n) || BIT(55-n) || BIT(47-n) || BIT(39-n) || BIT(31-n) || BIT(23-n) || BIT(15-n) || BIT(7-n)) //uint64_t com a coluna n do tabuleiro
//#define POS(l, c) (LINE(l) & COLUMN(c))
#define POS(l,c) (1LL << ((c) + ((l) << 3)))

enum PIECES {Blank_space, Pawn, Bishop, Queen, King, Rook, Knight};
typedef enum PIECES PIECE_T;

enum Color_e {BLACK, WHITE};
typedef enum Color_e Piece_Color;

struct Piece{
    uint8_t pos; // 4 fist bits -> collum , the other 4 -> row ... ex: 13 -> coluna 1, linha 3 ou 
    // seja A3 em notação oficial ... note-se que A significa que se começa a contar com 1
    // É importante aproveitar o espaço ao máximo para que na serial port seja mais fácil de passar
    // informação
    // VER a MAcro LSHUB_IN_BYTE
    PIECE_T p_type;
    Piece_Color color;
    uint8_t *map;
};
typedef struct Piece Piece_t; 
// TODO :::

// THIS SHOUD BE A FUNC with a switch that will call the apropriated get_valid_func according to type

Piece_t* make_piece(const xpm_map_t xpm, enum xpm_image_type type, uint8_t pos, PIECE_T p_t, Piece_Color color);

uint64_t get_valid_moves(Piece_t piece, uint8_t lin, uint8_t col, bool valid_moves[8][8]); // IGNORE THIS FOR NOW

// do this types of functs for every piece ...
uint64_t get_Pawn_valid_moves(uint8_t lin, uint8_t col,   bool valid_moves[8][8]);
uint64_t get_Bishop_valid_moves(uint8_t lin, uint8_t col, bool valid_moves[8][8]);
uint64_t get_Queen_valid_moves(uint8_t lin, uint8_t col,  bool valid_moves[8][8]);
uint64_t get_King_valid_moves(uint8_t lin, uint8_t col,   bool valid_moves[8][8]);
uint64_t get_Rook_valid_moves(uint8_t lin, uint8_t col,   bool valid_moves[8][8]);
uint64_t get_Knight_valid_moves(uint8_t lin, uint8_t col, bool valid_moves[8][8]);


//Auxiliar

bool is_inside_board(uint8_t lin, uint8_t col);
uint8_t get4LSB(uint8_t val);
uint8_t get4MSB(uint8_t val);


#endif