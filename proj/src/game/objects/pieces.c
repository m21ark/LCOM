#include "pieces.h"

int get_square_color(uint16_t lin, uint16_t col) {
  if ((lin + col) % 2)
    return BLACK;
  return WHITE;
}

Piece_t *make_piece(AnimSprite *animSprite, PIECE_T p_t, Piece_Color color) {
  Piece_t *new_piece = (Piece_t *) malloc(sizeof(Piece_t));

  if (animSprite != NULL)
    new_piece->animSprite = animSprite;

  new_piece->p_type = p_t;
  new_piece->color = color;

  return new_piece;
}

void free_piece(Piece_t *p) {
  // free(p->map);
  free(p);
}

void get_valid_moves(Board board[8][8], uint8_t lin, uint8_t col, bool valid_moves[8][8], bool isWhitesTurn) {
  memset((void *) valid_moves, 0, sizeof(bool) * BOARD_SIZE * BOARD_SIZE);

  if ((board[lin][col]->color == WHITE && !isWhitesTurn) ||
      (board[lin][col]->color == BLACK && isWhitesTurn)) {
    return;
  }

  switch (board[lin][col]->p_type) {
    case Pawn:
      get_Pawn_valid_moves(board, lin, col, valid_moves);
      return;
    case Bishop:
      get_Bishop_valid_moves(board, lin, col, valid_moves);
      return;
    case King:
      get_King_valid_moves(board, lin, col, valid_moves);
      return;
    case Queen:
      get_Queen_valid_moves(board, lin, col, valid_moves);
      return;
    case Knight:
      get_Knight_valid_moves(board, lin, col, valid_moves);
      return;
    case Rook:
      get_Rook_valid_moves(board, lin, col, valid_moves);
      return;
    default:
      break;
  }
}

bool valid_pawn_move(Board board[8][8], bool valid_moves[8][8], uint8_t lin, uint8_t col, uint8_t color) {
  bool b = board[lin][col]->p_type == Blank_space;
  valid_moves[lin][col] = b;
  return b;
}

void valid_pawn_eat(Board board[8][8], bool valid_moves[8][8], uint8_t lin, uint8_t col, uint8_t color) {
  if (lin < 0 || col < 0 || lin > 7 || col > 7)
    return;
  valid_moves[lin][col] = isEnemyPiecePos(board[lin][col], color);
}

void get_Pawn_valid_moves(Board board[8][8], uint8_t lin, uint8_t col, bool valid_moves[8][8]) {

  uint8_t color = board[lin][col]->color;

  if (board[lin][col]->color == WHITE) {

    valid_pawn_eat(board, valid_moves, lin - 1, col - 1, color);
    valid_pawn_eat(board, valid_moves, lin - 1, col + 1, color);

    if (lin == 6) {
      if (valid_pawn_move(board, valid_moves, lin - 1, col, color))
        valid_pawn_move(board, valid_moves, lin - 2, col, color);
    }
    else
      valid_pawn_move(board, valid_moves, lin - 1, col, color);
  }
  else {

    valid_pawn_eat(board, valid_moves, lin + 1, col - 1, color);
    valid_pawn_eat(board, valid_moves, lin + 1, col + 1, color);

    if (lin == 1) {
      if (valid_pawn_move(board, valid_moves, lin + 1, col, color))
        valid_pawn_move(board, valid_moves, lin + 2, col, color);
    }
    else
      valid_pawn_move(board, valid_moves, lin + 1, col, color);
  }
}

void get_Bishop_valid_moves(Board board[8][8], uint8_t lin, uint8_t col, bool valid_moves[8][8]) {
  bool color = board[lin][col]->color;

  for (int i = 1; i < 8; i++)
    if (col + i < 8 && lin + i < 8) {
      if (isOwnPiecePos(board[lin + i][col + i], color))
        break;
      valid_moves[lin + i][col + i] = true;
      if (isEnemyPiecePos(board[lin + i][col + i], color))
        break;
    }

  for (int i = 1; i < 8; i++)
    if (col - i >= 0 && lin - i >= 0) {
      if (isOwnPiecePos(board[lin - i][col - i], color))
        break;
      valid_moves[lin - i][col - i] = true;
      if (isEnemyPiecePos(board[lin - i][col - i], color))
        break;
    }

  for (int i = 1; i < 8; i++)
    if (col - i >= 0 && lin + i < 8) {
      if (isOwnPiecePos(board[lin + i][col - i], color))
        break;
      valid_moves[lin + i][col - i] = true;
      if (isEnemyPiecePos(board[lin + i][col - i], color))
        break;
    }

  for (int i = 1; i < 8; i++)
    if (lin - i >= 0 && col + i < 8) {
      if (isOwnPiecePos(board[lin - i][col + i], color))
        break;
      valid_moves[lin - i][col + i] = true;
      if (isEnemyPiecePos(board[lin - i][col + i], color))
        break;
    }
}

void get_Queen_valid_moves(Board board[8][8], uint8_t lin, uint8_t col, bool valid_moves[8][8]) {
  get_Rook_valid_moves(board, lin, col, valid_moves);
  get_Bishop_valid_moves(board, lin, col, valid_moves);
}

void valid_king_move(Board board[8][8], bool valid_moves[8][8], uint8_t lin, uint8_t col, uint8_t color) {
  if (is_inside_board(lin, col) && !isOwnPiecePos(board[lin][col], color))
    valid_moves[lin][col] = true;
}

void get_King_valid_moves(Board board[8][8], uint8_t lin, uint8_t col, bool valid_moves[8][8]) {

  uint8_t color = board[lin][col]->color;
  valid_king_move(board, valid_moves, lin - 1, col - 1, color);
  valid_king_move(board, valid_moves, lin - 1, col, color);
  valid_king_move(board, valid_moves, lin - 1, col + 1, color);
  valid_king_move(board, valid_moves, lin, col - 1, color);
  valid_king_move(board, valid_moves, lin, col + 1, color);
  valid_king_move(board, valid_moves, lin + 1, col - 1, color);
  valid_king_move(board, valid_moves, lin + 1, col, color);
  valid_king_move(board, valid_moves, lin + 1, col + 1, color);
}

void get_Rook_valid_moves(Board board[8][8], uint8_t lin, uint8_t col, bool valid_moves[8][8]) {

  bool color = board[lin][col]->color;
  Piece_t *pos;

  for (int i = col + 1; i < 8; i++) {
    pos = board[lin][i];
    if (isOwnPiecePos(pos, color))
      break;
    valid_moves[lin][i] = true;
    if (isEnemyPiecePos(pos, color))
      break;
  }

  for (int i = col - 1; i >= 0; i--) {
    pos = board[lin][i];
    if (isOwnPiecePos(pos, color))
      break;
    valid_moves[lin][i] = true;
    if (isEnemyPiecePos(pos, color))
      break;
  }

  for (int i = lin + 1; i < 8; i++) {
    pos = board[i][col];
    if (isOwnPiecePos(pos, color))
      break;
    valid_moves[i][col] = true;
    if (isEnemyPiecePos(pos, color))
      break;
  }

  for (int i = lin - 1; i >= 0; i--) {
    pos = board[i][col];
    if (isOwnPiecePos(pos, color))
      break;
    valid_moves[i][col] = true;
    if (isEnemyPiecePos(pos, color))
      break;
  }
}

void valid_knight_move(Board board[8][8], bool valid_moves[8][8], uint8_t lin, uint8_t col, uint8_t color) {
  if (is_inside_board(lin, col) && !isOwnPiecePos(board[lin][col], color))
    valid_moves[lin][col] = true;
}

void get_Knight_valid_moves(Board board[8][8], uint8_t lin, uint8_t col, bool valid_moves[8][8]) {

  uint8_t color = board[lin][col]->color;
  valid_knight_move(board, valid_moves, lin + 2, col + 1, color);
  valid_knight_move(board, valid_moves, lin + 2, col - 1, color);
  valid_knight_move(board, valid_moves, lin - 2, col + 1, color);
  valid_knight_move(board, valid_moves, lin - 2, col - 1, color);
  valid_knight_move(board, valid_moves, lin + 1, col + 2, color);
  valid_knight_move(board, valid_moves, lin + 1, col - 2, color);
  valid_knight_move(board, valid_moves, lin - 1, col + 2, color);
  valid_knight_move(board, valid_moves, lin - 1, col - 2, color);
}

bool isEnemyPiecePos(Piece_t *pos, int color) {
  return ((pos->p_type != Blank_space) && (pos->color != color));
}

bool isOwnPiecePos(Piece_t *pos, int color) {
  return ((pos->p_type != Blank_space) && (pos->color == color));
}

bool is_inside_board(uint8_t lin, uint8_t col) {
  return !(lin < 0 || lin > 7 || col < 0 || col > 7);
}
