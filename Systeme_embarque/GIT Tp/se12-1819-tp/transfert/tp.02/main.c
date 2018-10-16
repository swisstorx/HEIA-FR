/**
 * Copyright 2018 University of Applied Sciences Western Switzerland / Fribourg
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Project:		HEIA-FR / Embedded Systems 2 Laboratory
 *
 * Abstract:	TODO
 *
 * Purpose:		TODO
 *
 * Author: 		Marc Roten / Sven Rouvinez
 * Date: 		2018-10-01
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <am335x_gpio.h>
#include "wheel.h"
#include "serpent.h"
#include "seg7.h"
#include "buttons.h"
#include "counter.h"
#include "leds.h"

// -- constants & variable declaration ---------------------------------------

// delays
#define DELAY_ON	0x06ffff
#define DELAY_OFF	0x00ffff

#define S1			(1<<15)
#define S2			(1<<16)
#define S3			(1<<17)
#define LED1 	 	(12)
#define LED2		(13)
#define LED3		(14)

// macro to compute number of elements of an array
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

void initialize() {
	buttons_init();
	leds_init();
	wheel_init();
	seg_init();
}

void start_counter() {
	struct personne {
		char c;
		char a;
		char b;
	} pers_a = { 'a', 'b', 'c' };


	 personne pers_b= { 'a', 'b', 'c' };
	while (true) {
		uint32_t button_state = get_states_buttons();
		if (get_wheel_direction() == WHEEL_LEFT) {
			updateCounter(2);
		} else if (get_wheel_direction() == WHEEL_RIGHT) {
			updateCounter(1);
		} else if ((button_state & S2) == 0 || (button_state & S3) == 0) {
			break;
		}

	}

}

void start_snake() {

	while (true) {
		uint32_t button_state = get_states_buttons();
		if (get_wheel_direction() == WHEEL_LEFT) {
			get_Serpent_state();
		} else if (get_wheel_direction() == WHEEL_RIGHT) {
			get_Serpent_state();
		} else if ((button_state & S1) == 0 || (button_state & S3) == 0) {
			break;
		}

	}

}

int main() {
	initialize();

	while (true) {
		uint32_t button_state = get_states_buttons();
		set_number(1, 0);
		if ((button_state & S1) == 0) {
			set_state_by_led(LED1, true);
			set_state_by_led(LED2, false);
			set_state_by_led(LED3, false);

			start_counter();
		} else if ((button_state & S2) == 0) {
			set_state_by_led(LED1, false);
			set_state_by_led(LED2, true);
			set_state_by_led(LED3, false);
			start_snake();
		} else if ((button_state & S3) == 0) {
			set_state_by_led(LED1, false);
			set_state_by_led(LED2, false);
			set_state_by_led(LED3, true);
			initialize();

		}
	}

	return 0;

}

