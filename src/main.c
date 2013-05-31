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

uint8_t noise;
uint8_t a,b,c,x;

init_rng(s1,s2,s3) {
  //XOR new entropy into key state
  a ^=s1;
  b ^=s2;
  c ^=s3;
  x++;
}
 
uint8_t randomize()
{
  x++;
  a = (a^c^x);
  b = (b+c);  
  c = (c+(b>>1)^a);
  return(c);
}

void initLetters(uint8_t position) {
  character = daftOrder[position];
  bitPos = 7;
}

void incLetters() {
  position += 1;
  if (position > 10) {
    position = 0;
    printSpaces = 12;
    noise = randomize() / 2;
  } else {
    printSpaces = 2;
  }

  if (daftOrder[position] == 0) {
    printSpaces = 4;
    position++;    
  }

  initLetters(position);
}

void drawLetters() {
  uint8_t i;
  for (i = 0; i < 8; i++) {

    display[i] = display[i] << 1;

    if (!printSpaces) {
      uint8_t rowData = pgm_read_byte(&(daftLetters[((character - 1) * 8) + i]));
      rowData = rowData >> bitPos;

      display[i] = display[i] | rowData;
    }
  }

  if (!printSpaces) {
    bitPos--;
    if (bitPos - (7 - daftWidths[position]) == 0) {
      incLetters();
    }
  } else {
    printSpaces--;
  }

  _delay_ms(80);
}


void drawNoise() {
  int i;
  for (i = 0; i < 8; i++) {
    uint8_t rnd = randomize();
    display[i] = 0;
    if (rnd > 160) {
      display[i] = rnd;
    }
  }
  uint8_t wait = randomize();
  for (i = 0; i < wait; i++) {
    _delay_us(500);
  }
}

int main() { 

	// Set DDR direction to outbound
  DEBUG_DDR     |= 1 << DEBUG_PIN;
  SPI_DTA_DDR   |= 1 << SPI_DTA_PIN;
  SPI_CLK_DDR   |= 1 << SPI_CLK_PIN;
  SPI_LOAD_DDR  |= 1 << SPI_LOAD_PIN;

  initDisplay();
  initLetters(0);
  init_rng(5, 30, 0xfe);
  noise = 0x80;

  for (;;) {
    if (!noise) {
      drawLetters();
    } else {
      drawNoise();
      noise--;
      if (!noise) {
        printSpaces = 4;
        int i;
      }
    }
    writeBuffer();
  }
}
