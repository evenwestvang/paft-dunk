
#include <avr/sleep.h>
#include <util/delay.h>
#include "devices.h"

void setDebugLed(uint8_t val) {
 if (val) {
  DEBUG_PORT |= 1 << DEBUG_PIN;     // LED on
 } else {
  DEBUG_PORT &= ~(1 << DEBUG_PIN);  // LED off
 }
}

void hello(void) {
  // Say hi to everyone with your debug LED
  uint8_t led = 0;
  uint8_t i = 0;
  for(i = 0; i < 4; i++) {
    led = ~led;
    _delay_ms(50);
    setDebugLed(led);
  }
}
