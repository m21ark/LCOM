/**
 * @file keyboard.h
 * @brief Kbd Api
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef _LCOM_KBD_H_
#define _LCOM_KBD_H_

#include <lcom/lcf.h>

#include "../kbc/i8042.h"
#include "../kbc/kbc.h"
#include "../utils/handlers.h"

/**
 * @brief Reads Keyboard Scancode Bytes from the KBC Output Buffer
 * @param code[] Array where the Scancode Bytes are stored after reading
 * @param *size Size of the code[] array
 * @return EXIT_SUCCESS on success
 */
int(kbd_poll)(uint8_t code[], uint8_t *size);

/**
 * @brief Sets bits 0 and 1 of the Output Buffer to 1
 * @return EXIT_SUCCESS on success
 */
int(kbd_restore)();

/**
 * @brief Tests the KBC Interface
 * @return Status Byte Read from the Status Register
 */
int(kbc_kbd_interface_cmd)();

/**
 * @brief Enables KBC Interface
 * @return EXIT_SUCCESS on success
 */
int(kbc_enable_kbd_cmd)();

/**
 * @brief Disables KBC Interface
 * @return EXIT_SUCCESS on success
 */
int(kbc_disable_kbd_cmd)();

/**
 * @brief Issue a kbc enable command
 * @return EXIT_SUCCESS on success
 */
int(kbc_enable_kbd_cmd)();

/**
 * @brief Issue a kbc disable command
 * @return EXIT_SUCCESS on success
 */
int(kbc_disable_kbd_cmd)();

#endif
