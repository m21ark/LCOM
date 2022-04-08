#ifndef _LCOM_KBD_H_
#define _LCOM_KBD_H_

#include <lcom/lcf.h>

uint8_t scancode[2];
int scancode_sz;
bool two_byte_scancode;
bool error_flag;


int (subscribe_kbc_interrupt)(uint8_t bit_no, int *hook_id); // CHANGE THIS FROM HERE
int (unsubscribe_interrupt)(int *hook_id);
int (kbc_read_i)();
bool (kbc_get_error)();
void (kbc_ih)(void);
bool (kbc_ready)();
void (kbc_get_scancode)(unsigned char *scan, int* scan_sz);


int (kbd_read)(uint8_t * code);
int (kbd_poll)(uint8_t code[], uint8_t *size);
int (kbc_write_cmd)(uint8_t cmd, int port); // TODO 
int (kbd_restore)(); 


#endif
