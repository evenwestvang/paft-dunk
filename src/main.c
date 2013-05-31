/*
    WRITE DAFT PUNK ON A 8X8 LED MATRIX
*/

#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include "7219.h"
#include "daftpunk.h"

uint8_t position = 0;
uint8_t character;
uint8_t bitPos;
uint8_t printSpaces;

void initLetters(uint8_t position) {
  character = daftOrder[position];
  bitPos = 7;
}

void incLetters() {
  position += 1;
  if (position > 8) {
    position = 0;
    printSpaces = 12;
  } else {
    printSpaces = 3;
  }

  if (daftOrder[position] == 0) {
    printSpaces = 6;
    position += 1;    
  }

  initLetters(position);
}

void drawLetters() {

  uint8_t i;
  for (i = 0; i < 8; i++) {
    // Scroll display
    display[i] = display[i] << 1;

    if (!printSpaces) {
      // Read letter from program memory
      uint8_t rowData = pgm_read_byte(&(daftLetters[((character - 1) * 8) + i]));
      rowData = rowData >> bitPos;

      display[i] = display[i] | rowData;
    }
  }

  if (!printSpaces) {
    bitPos -= 1;
    if (bitPos == 0) {
      incLetters();
    }
  } else {
    printSpaces -= 1;
  }

  _delay_ms(20);
}

int main() { 

	// Set DDR direction to outbound
  DEBUG_DDR     |= 1 << DEBUG_PIN;
  SPI_DTA_DDR   |= 1 << SPI_DTA_PIN;
  SPI_CLK_DDR   |= 1 << SPI_CLK_PIN;
  SPI_LOAD_DDR  |= 1 << SPI_LOAD_PIN;

  initDisplay();
  initLetters(0);

  for (;;) {
    _delay_ms(30);
    drawLetters();
    writeBuffer();
  }
}
