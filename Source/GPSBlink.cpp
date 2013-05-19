#include "Light.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <avr/sleep.h>
#include <util/delay.h>

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz       0x00
#define CPU_8MHz        0x01
#define CPU_4MHz        0x02
#define CPU_2MHz        0x03
#define CPU_1MHz        0x04
#define CPU_500kHz      0x05
#define CPU_250kHz      0x06
#define CPU_125kHz      0x07
#define CPU_62kHz       0x08


const uint8_t LIGHT_COUNT = 15;
Light lights[LIGHT_COUNT];

void set_up_lights();
void set_up_io();
void set_up_timer();

ISR(TIMER1_COMPA_vect) {
	for(uint8_t i(0); i < LIGHT_COUNT; ++i)
		lights[i].Tick();
}

int main() {
	cli();

	CPU_PRESCALE(CPU_62kHz);	// power supply still ramping up voltage
	_delay_ms(500);
	CPU_PRESCALE(CPU_500kHz);

	set_up_io();
	set_up_lights();
	set_up_timer();

	// Enable interrupts.
	sei();

	// Configure what happens when sleeping.
	set_sleep_mode(SLEEP_MODE_IDLE);
	while (1)
		// Go to sleep. When the interrupt happens the sleep returns
		// but the while loops just puts us to sleep again.
		sleep_mode();
}

void set_up_timer() {
	// Set the timer interrupt mask register so that output compare A
	// match interrupts are enabled. _BV (bit value) macro converts
	// the bit number, OCIE1A in this case, into the appropriate byte
	// value.
	TIMSK1 = _BV(OCIE1A);

	// Configure the timer.
	// "14.10.3 Timer/Counter1 Control Register B" and "Table 14-5" in
	// the spec explain the prescaler values.
	// "14.8 Modes of Operation" in the spec "explains" WGM values.
	// Note that the 4 WMG bits are split between control registers A
	// and B.
	// Only need to modify the Timer/Counter1 Control Register B.
	TCCR1B |=
		// Prescaler divides the clock rate by 1024.
		//(_BV(CS12) | _BV(CS10))  |
		_BV(CS10) |
		// Set WGM12 bit to clear timer on compare with the OCR1A
		// register.
		_BV(WGM12);

	// Set Output Compare Register A for Timer/Counter1 to this value.
	OCR1A = 5000;
}

void set_up_io() {
	// Turn on all outputs
	PORTB = 0xFF;
	PORTD = 0x00;

	// Set all pins on all ports to outputs
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;
	DDRE = 0xFF;
	DDRF = 0xFF;

	// Let the user see all the pretty lights for a few seconds
	_delay_ms(6000);

	// Turn off the outputs
	PORTB = 0x00;
	PORTD = 0xFF;

	// Let the user think they broke it for a few seconds
	_delay_ms(6000);
	
	// Turn off diagnostic LED
	PORTD &= ~_BV(6);
}

void set_up_lights() {
	lights[0].count = 1;
	lights[0].clock_divisor = 80;
	lights[0].pin = 0;
	lights[0].port = 1;
	lights[0].active_high = true;

	lights[1].count = 2;
	lights[1].clock_divisor = 81;
	lights[1].pin = 1;
	lights[1].port = 1;
	lights[1].active_high = true;

	lights[2].count = 3;
	lights[2].clock_divisor = 82;
	lights[2].pin = 2;
	lights[2].port = 1;
	lights[2].active_high = true;

	lights[3].count = 4;
	lights[3].clock_divisor = 83;
	lights[3].pin = 3;
	lights[3].port = 1;
	lights[3].active_high = true;

	lights[4].count = 5;
	lights[4].clock_divisor = 84;
	lights[4].pin = 4;
	lights[4].port = 1;
	lights[4].active_high = true;

	lights[5].count = 6;
	lights[5].clock_divisor = 85;
	lights[5].pin = 5;
	lights[5].port = 1;
	lights[5].active_high = true;

	lights[6].count = 7;
	lights[6].clock_divisor = 86;
	lights[6].pin = 6;
	lights[6].port = 1;
	lights[6].active_high = true;

	
	lights[7].count = 8;
	lights[7].clock_divisor = 87;
	lights[7].pin = 7;
	lights[7].port = 1;
	lights[7].active_high = true;
	
	lights[8].count = 9;
	lights[8].clock_divisor = 88;
	lights[8].pin = 0;
	lights[8].port = 3;
	lights[8].active_high = false;

	lights[9].count = 10;
	lights[9].clock_divisor = 89;
	lights[9].pin = 1;
	lights[9].port = 3;
	lights[9].active_high = false;

	lights[10].count = 11;
	lights[10].clock_divisor = 90;
	lights[10].pin = 2;
	lights[10].port = 3;
	lights[10].active_high = false;

	lights[11].count = 12;
	lights[11].clock_divisor = 91;
	lights[11].pin = 3;
	lights[11].port = 3;
	lights[11].active_high = false;

	lights[12].count = 13;
	lights[12].clock_divisor = 92;
	lights[12].pin = 4;
	lights[12].port = 3;
	lights[12].active_high = false;

	lights[13].count = 14;
	lights[13].clock_divisor = 93;
	lights[13].pin = 5;
	lights[13].port = 3;
	lights[13].active_high = false;

	lights[14].count = 15;
	lights[14].clock_divisor = 94;
	lights[14].pin = 7;
	lights[14].port = 3;
	lights[14].active_high = false;
}
