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
 * Project:	HEIA-FR / Embedded Systems 1 Laboratory
 *
 * Abstract: Introduction the C programming language
 *
 * Purpose:	Simple C program implementing basic access to the GPIO modules of
 *			the AM3358 microprocessor to control the wheel and the 7-segment
 * 			display of the HEIA-FR extension card of the Beaglebone Black board.
 *
 * Author: 	Daniel Gachet
 * Date: 	15.10.2018
 */

#include <stdio.h>
#include <stdbool.h>

#include "buttons.h"
#include "leds.h"
#include "seg7.h"
#include "counter.h"
#include "serpentine.h"

enum modes {COUNTER, SERPENTINE};

int main()
{
	// print program banner
	printf ("HEIA-FR - Embedded Systems 1 Laboratory\n"
			"An introduction the C programming language\n"
			"--> 7-segment and wheel demo program\n");

	// initialization 
	buttons_init();
	leds_init();
	seg7_init();
	counter_init();
	serpentine_init();

	// main loop
	enum modes mode = COUNTER;
	while (true) {
		uint32_t led_state = 0;
		uint32_t buttons = buttons_get_state();

		bool reset = (buttons & BUTTONS_3) != 0;
		if (reset) {
			led_state |= LEDS_3;
			counter_reset();
			serpentine_reset();
		}

		if ((buttons & BUTTONS_1) != 0) mode = COUNTER;
		if (mode == COUNTER) {
			led_state |= LEDS_1;
			counter_process();
		}

		if ((buttons & BUTTONS_2) != 0) mode = SERPENTINE;
		if (mode == SERPENTINE) {
			led_state |= LEDS_2;
			serpentine_process();
		}

		leds_set_state(led_state);
		seg7_refresh_display();
	}

	return 0;
}
