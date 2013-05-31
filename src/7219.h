#ifndef _7219_H
#define _7219_H

#include "devices.h"
#include <avr/io.h>

uint8_t display[8];

void initDisplay();
int writeWord(int word);
void writeBuffer();

#endif