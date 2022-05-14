#include <lcom/lcf.h>

#include <stdint.h>
#include "handlers.h"

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  
  NullSafety(lsb);
  *lsb = val;

  return EXIT_SUCCESS;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {

  NullSafety(msb);
  *msb = val >> 8;

  return EXIT_SUCCESS;
}

int (util_sys_inb)(int port, uint8_t *value) {
  NullSafety(value);
  
  uint32_t p;
  CHECKCall(sys_inb(port, &p));
  
  *value = (uint8_t)p;

  return EXIT_SUCCESS;
}
