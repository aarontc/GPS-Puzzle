#include "Light.h"

#include <avr/io.h>

/**
 * @brief Constructor for the Light class.
 * Sets the initial state to LIGHT_OFF and the tick count to OFF_TICKS to cause an immediate transition to LIGHT_ON.
 **/
Light::Light()
	: current_count(0)
	, current_state_ticks(OFF_TICKS)
	, current_state(LIGHT_OFF)
	{ }


void Light::SetState(LightState state) {
	current_state_ticks = 0;
	current_state = state;

	switch(current_state) {
		case LIGHT_QUIET:
			current_count = 0;
			SetOutput(false);
			break;
		
		case LIGHT_OFF:
			SetOutput(false);
			break;
			
		case LIGHT_ON:
			++current_count;
			SetOutput(true);
			break;
	}
}

void Light::Tick() {
	++current_state_ticks;

	switch(current_state) {
		case LIGHT_QUIET:
			if(current_state_ticks >= (OFF_TICKS * QUIET_CYCLES))
				SetState(LIGHT_ON);
			break;
			
		case LIGHT_OFF:
			if(current_state_ticks >= OFF_TICKS)
				SetState(LIGHT_ON);
			break;
			
		case LIGHT_ON:
			if(current_state_ticks >= clock_divisor)
				if(current_count >= count) {
					SetState(LIGHT_QUIET);
				} else {
					SetState(LIGHT_OFF);
				}
			break;
	}
}

void Light::SetOutput(bool on) {
	if(!active_high)
		on = !on;

	uint8_t value(_BV(pin));

	if(port == 1) {
		if(on) {
			PORTB |= value;
		} else {
			PORTB &= ~value;
		}
	} else if(port == 3) {
		if(on) {
			PORTD |= value;
		} else {
			PORTD &= ~value;
		}
	}
}
