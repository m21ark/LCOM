/**
 * @file mouse.h
 * @brief Mouse API
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef _LCOM_MOUSE_H_
#define _LCOM_MOUSE_H_

#include <lcom/lcf.h>

#include "../../assets/cursor.xpm"
#include "../../game/views/sprite/sprite.h"
#include "../kbc/i8042.h"
#include "../kbc/kbc.h"
#include "../utils/handlers.h"

typedef struct packet packet_t;

/**
 * @brief Parses mouse data into a packet struct data type
 * @param data Data obtained from the mouse
 * @return Data parsed to a Packet Struct
 */
packet_t mouse_data_to_packet(uint8_t *data);

/**
 * @brief Disables Mouse Data Reporting using kbc_send_mouse_cmd()
 * @return EXIT_SUCCESS on success
 */
int mouse_disable_data_reporting();

/**
 * @brief Enables Mouse Data Reporting using kbc_send_mouse_cmd()
 * @return EXIT_SUCCESS on success
 */
int _mouse_enable_data_reporting_();

typedef sprite_t *mouse_ptr;

/**
 * @brief Detects mouse events happening in a packet
 * @param pp Packet Struct
 * @return struct mouse_ev* Struct containing info about the detected event
 */
struct mouse_ev *mouse_get_event(struct packet *pp);

#endif
