#ifndef _ANALOG_H
#define _ANALOG_H

#include <avr/io.h>
      
void analog_init();
uint16_t analog_read(uint8_t channel);

#endif