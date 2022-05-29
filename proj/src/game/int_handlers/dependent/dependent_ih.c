#include "dependent_ih.h"

extern int (*state[])(struct mouse_ev *event);
extern int (*menu_state[])(struct mouse_ev *event, int x, int y);

EVENTS handle_evt(EVENTS event) {
  EVENTS ret = NO_EVT;

  if (event & BIT(TIMER_EVT)) {
    ret |= handle_timer_evt(event);
  }
  if (event & BIT(KBD_EVT)) {
    ret |= handle_kbd_evt(event);
  }
  if (event & BIT(MOUSE_EVT)) {
    ret |= handle_mouse_evt(event);
  }

  return ret;
}

EVENTS handle_timer_evt(EVENTS event) {
  static int counter = 0;
  //static int frames = 0;
  static int ticks_frame = 2; // TODO: MAGIC
  static int16_t speed = 10;
  //static int mov = 1;
  counter++;
  if (speed > 0)
    if (counter % ticks_frame == 0) {

      //// vg_draw_rectangle(0, 0, get_hres(), get_vres(), 0x0);
      //if (mov == 1) {
      //  frames++;
      //  // if (frames % (-speed) != 0)
      //  //   return BREAK_EVT;
      //}
//
      //if (move_right) // TODO: CHECK THE BOUNDARIES
      //{
      //  // if (get_sprite_X(sprite) + speed + get_sprite_W(sprite) <= get_hres())
      //  //   set_sprite_X(sprite, get_sprite_X(sprite) + speed);
      //} //
      //if (move_left) {
      //  // if (get_sprite_X(sprite) >= (uint32_t) speed)
      //  //   set_sprite_X(sprite, get_sprite_X(sprite) - speed);
      //}
      //if (move_down) {
      //  // if (get_sprite_Y(sprite) + speed + get_sprite_H(sprite) <= get_vres())
      //  //   set_sprite_Y(sprite, get_sprite_Y(sprite) + speed);
      //}
      //if (move_up) {
      //  // if (get_sprite_Y(sprite) >= (uint32_t) speed)
      //  //   set_sprite_Y(sprite, get_sprite_Y(sprite) - speed);
      //}
      draw_update();
    }

  return BIT(NO_EVT);
}
EVENTS handle_kbd_evt(EVENTS event) {
  if (!kbc_get_error()) {
    if (kbc_ready()) {
      kbc_get_scancode(scan, &scan_size);
      if (scan[scan_size - 1] == (ESC_BREAK_CODE))
        return BIT(BREAK_EVT);
      else if (scan[scan_size - 1] == RIGHT_ARROW)
        move_right = true;
      else if (scan[scan_size - 1] == LEFT_ARROW)
        move_left = true;
      else if (scan[scan_size - 1] == DOWN_ARROW)
        move_down = true;
      else if (scan[scan_size - 1] == UP_ARROW)
        move_up = true;
      else if (scan[scan_size - 1] == RELEASE_RIGHT_ARROW)
        move_right = false;
      else if (scan[scan_size - 1] == RELEASE_LEFT_ARROW)
        move_left = false;
      else if (scan[scan_size - 1] == RELEASE_DOWN_ARROW)
        move_down = false;
      else if (scan[scan_size - 1] == RELEASE_UP_ARROW)
        move_up = false;
    }
  }
  return NO_EVT;
}

EVENTS handle_mouse_evt(EVENTS event) {
  if (!kbc_get_error()) { // TODO: MAKE THE FUNC RETURN THE TYPES THAT WE READ
    if (kbc_mouse_ready()) {
      kbc_get_mouse_data(scan);
      struct packet pp = mouse_data_to_packet(scan);
    
      m_event = mouse_get_event(&pp);
      
      if (m_event->type == MOUSE_MOV)
        mouse_update_pos(m_event->delta_x, m_event->delta_y);

      state_fun = state[cur_state];
      rc = state_fun(m_event);

      cur_state = lookup_transitions(cur_state, rc);

      menu_state_fun = menu_state[menu_cur_state];

      menu_rc = menu_state_fun(m_event, get_cursor_X(), get_cursor_Y());
      menu_cur_state = menu_lookup_transitions(menu_cur_state, menu_rc);

      if (menu_cur_state == menu_end)
        return BIT(BREAK_EVT);

      game_set_state(menu_cur_state);
    }
  }
  return NO_EVT;
}