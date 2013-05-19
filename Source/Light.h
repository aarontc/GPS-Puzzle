#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <stdint.h>


class Light {
	static const uint8_t QUIET_CYCLES = 3;
	static const uint8_t OFF_TICKS = 80;
	
	enum LightState {
		LIGHT_QUIET,							/**< The light is waiting after completing a flash cycle. */
		LIGHT_ON,								/**< The light is working through a flash cycle and is currently on. */
		LIGHT_OFF								/**< The light is working through a flash cycle and is currently off. */
	};

	public:
		/**
		 * @brief Default constructor
		 **/
		Light();

		/**
		 * @brief Moves the state machine forward
		 **/
		void Tick();

		uint8_t count;							/**< The number we are representing (times to change state before a long delay) */
		uint16_t clock_divisor;					/**< Number of clock ticks before we change from on state */
		uint8_t pin;							/**< Pin index into the port */
		uint8_t port;							/**< Port index (A == 0, B == 1, etc.) */
		bool active_high;						/**< Indicates whether the LED is active low or high */

	private:
		/**
		 * @brief Main worker function
		 **/
		void SetState(LightState state);

		/**
		 * @brief Turns on the light
		 **/
		void SetOutput(bool on);


		uint8_t current_count;					/**< How far are we through the count? */
		uint16_t current_state_ticks;			/**< Number of ticks we have seen since last state change */
		
		LightState current_state;
};

#endif
