#include "devices.h"
#include <avr/io.h>
#include <util/delay.h>

uint8_t display[8];

void initDisplay() {
  // All digits on
  writeWord(0x0b07);
  // Set maximum brightness
  writeWord(0x0a0f);
  // Turn it on
  writeWord(0x0c01);
}

int writeWord(int word) {
  SPI_LOAD_PORT &= ~(1 << SPI_LOAD_PIN);
  int i;
  for (i = 0; i < 16; i++) {
    if (word & 0b1000000000000000) {
      SPI_DTA_PORT |= 1 << SPI_DTA_PIN;
    } else {
      SPI_DTA_PORT &= ~(1 << SPI_DTA_PIN);
    }
    SPI_CLK_PORT |= 1 << SPI_CLK_PIN;  
    SPI_CLK_PORT &= ~(1 << SPI_CLK_PIN);
    word = word << 1;
  }
  SPI_LOAD_PORT |= 1 << SPI_LOAD_PIN;  
}

void writeBuffer() {
  int i;
  for (i = 0; i < 8; i++) {
    writeWord(0x0100 + (i * 0x100) + display[i]);
  }
}

