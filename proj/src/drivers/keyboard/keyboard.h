#ifndef _LCOM_KBD_H_
#define _LCOM_KBD_H_

#include <lcom/lcf.h>

#include "../kbc/i8042.h"
#include "../kbc/kbc.h"
#include "../utils/handlers.h"

int(kbd_poll)(uint8_t code[], uint8_t *size);
int(kbd_restore)();
int(kbc_kbd_interface_cmd)();

int(kbc_enable_kbd_cmd)();  // I THINK IT IS ALSO WORKING
int(kbc_disable_kbd_cmd)(); // WORKING

#endif
