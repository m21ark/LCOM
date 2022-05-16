#include "rgb.h"

uint8_t getRed_t(struct RGB *self) {
  return (self->value >> getRedFieldPosition()) & ((1 << getRedMaskSize()) - 1) ;
}
uint8_t getGreen_t(struct RGB *self) {
  return (self->value >> getGreenFieldPosition()) & ((1 << getGreenMaskSize()) - 1); 
}
uint8_t getBlue_t(struct RGB *self) {
  return (self->value >> getBlueFieldPosition()) & ((1 << getBlueMaskSize()) - 1); 
}

void setRed_t(struct RGB *self, uint8_t value) {

  uint32_t temp = (self->getGreen(self) << (getGreenFieldPosition())) | self->getBlue(self);

  temp |= (value) << (getRedFieldPosition());

  self->value = temp;
  return;
}
void setGreen_t(struct RGB *self, uint8_t value) {
  
  uint32_t temp = (self->getRed(self) << (getRedFieldPosition())) 
                | self->getBlue(self);

  temp |= ((value) << (getGreenFieldPosition()));

  self->value = temp;

  return ; 
}
void setBlue_t(struct RGB *self, uint8_t value) {
  
  uint32_t temp = (self->getGreen(self) << (getGreenFieldPosition())) 
                | (self->getRed(self) << (getRedFieldPosition()))  ;

  temp |= (value);

  self->value = temp;

  return;
}

void put_references(RGB * rgb) {
  rgb->getRed = getRed_t; 
  rgb->getGreen = getGreen_t; 
  rgb->getBlue = getBlue_t; 

  rgb->setRed = setRed_t; 
  rgb->setGreen = setGreen_t; 
  rgb->setBlue = setBlue_t; 
}

RGB RGB_new(uint32_t color) { 
  RGB obj;

  obj.value = color;

  put_references(&obj);

  return obj;
}
