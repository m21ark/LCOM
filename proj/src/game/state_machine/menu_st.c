#include "menu_st.h"

int (* menu_state[])(struct mouse_ev *event) = { 
  menu_entry_state, menu_multiplayer_state, menu_online_state , menu_exit_state};

int menu_entry_state(struct mouse_ev *event) {
  if (event->type == LB_PRESSED){
    return OP1;
  }
  return menu_repeat;
}

int menu_multiplayer_state(struct mouse_ev *event) {
  return menu_repeat;
}

int menu_online_state(struct mouse_ev *event) {
  return menu_repeat;
}


int menu_exit_state(struct mouse_ev *event) {
  return menu_repeat;
}

enum menu_state_codes menu_lookup_transitions( int cur_state, int rc) {

  MENU_ST_TRANS state_transitions[] = {
    {menu_entry, menu_repeat, menu_entry},
    {menu_entry, OP1, multiplayer},
    {menu_entry, OP2, online},
    {menu_entry, menu_back, menu_end},
    {multiplayer, menu_back, menu_entry},
    {multiplayer, menu_repeat, multiplayer},
    {online, menu_back, menu_entry},
    {online, menu_repeat, online}
  };

  for (size_t i = 0; i < 8; i++)
  {
    if (state_transitions[i].src_state == cur_state && state_transitions[i].ret_code == rc)
    {
      return state_transitions[i].dst_state;
    }
  }
  return cur_state;
}
