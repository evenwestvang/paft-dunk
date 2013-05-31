#include "analog.h"

void analog_init()
{
  // This part nicked from Orangutan Library file analog.c

  // The Orangutans have an external reference voltage on the AREF
	// pin tied to our +5V regulated Vcc.  We want to set our ADC to
	// use this as our reference.  The ADMUX register needs REFS0
	// set to 1, and REFS1 set to zero for this mode.
	ADMUX = (1 << REFS0);
	
	// The ADC Control and Status Register A sets up the rest of 
	// what we need.  Three bits ADPS0, 1, and 2, set the prescale
	// for how fast our conversions are done.  In this example
	// we use CPU/128, or mode 7:
	ADCSRA = (6 << ADPS0);	
  	
  	// Conversions take 13 ADC cycles to complete the sample and hold.
	// Dividing our CPU by 128 gives us 12019 samples/sec.
	// Finally, we enable the ADC subsystem:
	ADCSRA |= (1 << ADEN);
  
}

// Read out the specified analog channel to 10 bits (From Baby Orangutan library)
uint16_t analog_read(uint8_t channel) 
{
	// Begin by setting up the MUX so it knows which channel
	// to connect to the ADC:

	// Clear the channel selection (low 5 bits in ADMUX)
	ADMUX &= ~0x1F;

	// Select the specified channel
	ADMUX |= channel;

	// Now we initiate a conversion by telling the ADC's
	// control register to start conversion (ADSC):

	// ADC start conversion
	ADCSRA |= (1 << ADSC);

	// We wait for conversion to complete by watching the
	// ADSC bit on the ADCSRA register.  When it goes away,
	// the conversion is done:
	while (bit_is_set(ADCSRA, ADSC));

	// Since we're reading out ten bits, we have to read 
	// the results out of two different registers: ADCL for
	// the low byte, and ADCH for the high byte.  Caution
	// here:  We have to read ADCL before we read ADCH.
	// Since they're both just bytes, we have to shift the
	// high byte over by 8-bits and or the two together
	// to make the full 10-bit value:

	return (ADCL | ADCH << 8);	// read ADC (full 10 bits);
}
