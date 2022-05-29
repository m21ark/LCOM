#include "views.h"

extern uint8_t rtc_data[6]; 

void draw_board() {
  static int lookUpTable[] = {
    0, 94, 188, 282, 376, 470, 564, 658};

  for (size_t i = 0; i < BOARD_SIZE; i++) {
    for (size_t j = 0; j < BOARD_SIZE; j++) {
      vg_draw_rectangle(lookUpTable[i], lookUpTable[j], BOARD_SCREEN_CASE_SIZE, BOARD_SCREEN_CASE_SIZE, get_square_color(j, i) == WHITE ? BOARD_WHITE_CASE_COLOR : BOARD_BLACK_CASE_COLOR);
    }
  }
}

void draw_pieces(Board table[8][8]) {
  get_valid_moves(*(table[select_lin][select_col]), select_lin, select_col, moves);
  for (size_t i = 0; i < BOARD_SIZE; i++) {
    for (size_t j = 0; j < BOARD_SIZE; j++) {
      if (table[i][j]->p_type != Blank_space) {
        draw_piece(table[i][j], j, i);
      }
      if (moves[i][j]) {
        vg_draw_rectangle(lookUpTable[j], lookUpTable[i], BOARD_SCREEN_CASE_SIZE, BOARD_SCREEN_CASE_SIZE, 0xff0000);
      }
    }
  }
}

void draw_piece(Board piece, unsigned int x, unsigned int y) {
  if (piece == NULL) {
    return;
  }

  draw_piece_in_mode_14c(piece->map, lookUpTable[x], lookUpTable[y], BOARD_SCREEN_CASE_SIZE);
}

void draw_clock() {
}

void get_selected_valid_moves(bool arr[8][8]) {
  arr = moves;
}

void set_selected_case(int lin, int col) {
  for (size_t i = 0; i < 8; i++)
  {
    if (lin < lookUpTable[i] + BOARD_SCREEN_CASE_SIZE 
    && lin > lookUpTable[i])
    {
      select_lin = i;
    }
  }

  for (size_t i = 0; i < 8; i++)
  {
    if (col < lookUpTable[i] + BOARD_SCREEN_CASE_SIZE
    && col > lookUpTable[i])
    {
      select_col = i;
    }
  }
}


void mouse_update_pos(int x, int y) {
  int nx = get_sprite_X(cursor) + x;
  int ny = get_sprite_Y(cursor) - y;
  set_sprite_X(cursor, (nx > 0 ? nx : get_hres() + nx) % get_hres());
  set_sprite_Y(cursor, (ny > 0 ? ny : get_vres() + ny) % get_vres());
}

void set_bg() {
  menu_img = make_sprite(menu_bg, XPM_8_8_8_8);
  set_sprite_X(menu_img, 0);
  set_sprite_Y(menu_img, 0);
}

void set_cursor() {
  cursor = make_sprite(cursor_xpm, XPM_8_8_8_8);
  set_sprite_X(cursor, 200);
  set_sprite_Y(cursor, 200);
}

int get_cursor_X() {
  return get_sprite_X(cursor);
}

int get_cursor_Y() {
  return get_sprite_Y(cursor);
}

void draw_bg() {
  draw_sprite_in_mode_14c(menu_img);
}

void draw_cursor() {
  draw_sprite_in_mode_14c(cursor);
}

void draw_sprite(const char *xpm[], int x, int y) {
  sprite_t *sprite = make_sprite(xpm, XPM_8_8_8_8);
  set_sprite_X(sprite, x);
  set_sprite_Y(sprite, y);
  draw_sprite_in_mode_14c(sprite);
  free_sprite(sprite);
}

void draw_menu() {
  switch (game_cur_state) {
    case menu_entry:
      draw_sprite(play_b_xpm, 400, 200);
      draw_sprite(instructions_b_xpm, 400, 400);
      draw_sprite(exit_b_xpm, 400, 600);

      char temp[20];
  
      sprintf(temp, "%d:%d:%d  %d/%d/%d", rtc_data[2], rtc_data[1], rtc_data[0], rtc_data[3], rtc_data[4], rtc_data[5]);
      // "01:23:34  " + temp + "/03/21"
      draw_text(temp, 200, 780, 0xFF88FF);
      break;
    case menu_play:
      draw_sprite(multiplayer_b_xpm, 400, 200);
      draw_sprite(online_b_xpm, 400, 400);
      draw_sprite(back_b_xpm, 400, 600);
      break;
    case instructions:
      draw_sprite(instructions_b_xpm, 400, 200);
      draw_sprite(back_b_xpm, 400, 400);
      break;
    case multiplayer:
      // draw_sprite(multiplayer_b_xpm, 400, 200);
      draw_board();
      draw_pieces(board);
      // draw_sprite(back_b_xpm, 400, 400);
      break;
    case online:
      draw_sprite(online_b_xpm, 400, 200);
      draw_sprite(back_b_xpm, 400, 400);
      break;
    case menu_end:
      draw_sprite(back_b_xpm, 400, 200);
      draw_sprite(back_b_xpm, 400, 400);
      break;
    default:
      break;
  }
}

void game_set_state(enum menu_state_codes state) {
  game_cur_state = state;
}

void draw_update() {
  draw_bg();
  draw_menu();
  draw_cursor();
  flush_screen();
}


void set_up_view() {
  xpm_map_t m = menu_bg;
  menu_img = make_sprite(m, XPM_8_8_8_8);

  xpm_map_t cm = cursor_xpm;
  cursor = make_sprite(cm, XPM_8_8_8_8);

  set_sprite_X(cursor, 200);
  set_sprite_Y(cursor, 200);

  set_sprite_X(menu_img, 0);
  set_sprite_Y(menu_img, 0);

  draw_sprite_in_mode_14c(menu_img);
  draw_sprite_in_mode_14c(cursor);
}

void free_view() {
  free_sprite(cursor);
  free_sprite(menu_img);
}

void set_up_board() {
  board[0][0] = make_piece(wB, XPM_8_8_8_8, 0x00, Rook, BLACK);
  board[0][1] = make_piece(wB, XPM_8_8_8_8, 0x10, Knight, BLACK);
  board[0][2] = make_piece(wB, XPM_8_8_8_8, 0x20, Bishop, BLACK);
  board[0][3] = make_piece(wB, XPM_8_8_8_8, 0x30, Queen, BLACK);
  board[0][4] = make_piece(wB, XPM_8_8_8_8, 0x40, King, BLACK);
  board[0][5] = make_piece(wB, XPM_8_8_8_8, 0x50, Bishop, BLACK);
  board[0][6] = make_piece(wB, XPM_8_8_8_8, 0x60, Knight, BLACK);
  board[0][7] = make_piece(wB, XPM_8_8_8_8, 0x70, Rook, BLACK);
  board[1][0] = make_piece(wB, XPM_8_8_8_8, 0x01, Pawn, BLACK);
  board[1][1] = make_piece(wB, XPM_8_8_8_8, 0x11, Pawn, BLACK);
  board[1][2] = make_piece(wB, XPM_8_8_8_8, 0x21, Pawn, BLACK);
  board[1][3] = make_piece(wB, XPM_8_8_8_8, 0x31, Pawn, BLACK);
  board[1][4] = make_piece(wB, XPM_8_8_8_8, 0x41, Pawn, BLACK);
  board[1][5] = make_piece(wB, XPM_8_8_8_8, 0x51, Pawn, BLACK);
  board[1][6] = make_piece(wB, XPM_8_8_8_8, 0x61, Pawn, BLACK);
  board[1][7] = make_piece(wB, XPM_8_8_8_8, 0x71, Pawn, BLACK);
  board[2][0] = make_piece(wB, XPM_8_8_8_8, 0x02, Blank_space, BLACK);
  board[2][1] = make_piece(wB, XPM_8_8_8_8, 0x12, Blank_space, BLACK);
  board[2][2] = make_piece(wB, XPM_8_8_8_8, 0x22, Blank_space, BLACK);
  board[2][3] = make_piece(wB, XPM_8_8_8_8, 0x32, Blank_space, BLACK);
  board[2][4] = make_piece(wB, XPM_8_8_8_8, 0x42, Blank_space, BLACK);
  board[2][5] = make_piece(wB, XPM_8_8_8_8, 0x52, Blank_space, BLACK);
  board[2][6] = make_piece(wB, XPM_8_8_8_8, 0x62, Blank_space, BLACK);
  board[2][7] = make_piece(wB, XPM_8_8_8_8, 0x72, Blank_space, BLACK);
  board[3][0] = make_piece(wB, XPM_8_8_8_8, 0x03, Blank_space, BLACK);
  board[3][1] = make_piece(wB, XPM_8_8_8_8, 0x13, Blank_space, BLACK);
  board[3][2] = make_piece(wB, XPM_8_8_8_8, 0x23, Blank_space, BLACK);
  board[3][3] = make_piece(wB, XPM_8_8_8_8, 0x33, Blank_space, BLACK);
  board[3][4] = make_piece(wB, XPM_8_8_8_8, 0x43, Blank_space, BLACK);
  board[3][5] = make_piece(wB, XPM_8_8_8_8, 0x53, Blank_space, BLACK);
  board[3][6] = make_piece(wB, XPM_8_8_8_8, 0x63, Blank_space, BLACK);
  board[3][7] = make_piece(wB, XPM_8_8_8_8, 0x73, Blank_space, BLACK);
  board[4][0] = make_piece(wB, XPM_8_8_8_8, 0x04, Blank_space, BLACK);
  board[4][1] = make_piece(wB, XPM_8_8_8_8, 0x14, Blank_space, BLACK);
  board[4][2] = make_piece(wB, XPM_8_8_8_8, 0x24, Blank_space, BLACK);
  board[4][3] = make_piece(wB, XPM_8_8_8_8, 0x34, Blank_space, BLACK);
  board[4][4] = make_piece(wB, XPM_8_8_8_8, 0x44, Blank_space, BLACK);
  board[4][5] = make_piece(wB, XPM_8_8_8_8, 0x54, Blank_space, BLACK);
  board[4][6] = make_piece(wB, XPM_8_8_8_8, 0x64, Blank_space, BLACK);
  board[4][7] = make_piece(wB, XPM_8_8_8_8, 0x74, Blank_space, BLACK);
  board[5][0] = make_piece(wB, XPM_8_8_8_8, 0x05, Blank_space, BLACK);
  board[5][1] = make_piece(wB, XPM_8_8_8_8, 0x15, Blank_space, BLACK);
  board[5][2] = make_piece(wB, XPM_8_8_8_8, 0x25, Blank_space, BLACK);
  board[5][3] = make_piece(wB, XPM_8_8_8_8, 0x35, Blank_space, BLACK);
  board[5][4] = make_piece(wB, XPM_8_8_8_8, 0x45, Blank_space, BLACK);
  board[5][5] = make_piece(wB, XPM_8_8_8_8, 0x55, Blank_space, BLACK);
  board[5][6] = make_piece(wB, XPM_8_8_8_8, 0x65, Blank_space, BLACK);
  board[5][7] = make_piece(wB, XPM_8_8_8_8, 0x75, Blank_space, BLACK);
  board[6][0] = make_piece(wB, XPM_8_8_8_8, 0x06, Pawn, WHITE);
  board[6][1] = make_piece(wB, XPM_8_8_8_8, 0x16, Pawn, WHITE);
  board[6][2] = make_piece(wB, XPM_8_8_8_8, 0x26, Pawn, WHITE);
  board[6][3] = make_piece(wB, XPM_8_8_8_8, 0x36, Pawn, WHITE);
  board[6][4] = make_piece(wB, XPM_8_8_8_8, 0x46, Pawn, WHITE);
  board[6][5] = make_piece(wB, XPM_8_8_8_8, 0x56, Pawn, WHITE);
  board[6][6] = make_piece(wB, XPM_8_8_8_8, 0x66, Pawn, WHITE);
  board[6][7] = make_piece(wB, XPM_8_8_8_8, 0x76, Pawn, WHITE);
  board[7][0] = make_piece(wB, XPM_8_8_8_8, 0x07, Rook, WHITE);
  board[7][1] = make_piece(wB, XPM_8_8_8_8, 0x17, Knight, WHITE);
  board[7][2] = make_piece(wB, XPM_8_8_8_8, 0x27, Bishop, WHITE);
  board[7][3] = make_piece(wB, XPM_8_8_8_8, 0x37, Queen, WHITE);
  board[7][4] = make_piece(wB, XPM_8_8_8_8, 0x47, King, WHITE);
  board[7][5] = make_piece(wB, XPM_8_8_8_8, 0x57, Bishop, WHITE);
  board[7][6] = make_piece(wB, XPM_8_8_8_8, 0x67, Knight, WHITE);
  board[7][7] = make_piece(wB, XPM_8_8_8_8, 0x77, Rook, WHITE);
}