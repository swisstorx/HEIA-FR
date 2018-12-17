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
 * Abstract: Switches Device Driver
 *
 * Purpose:	This module implements a method to get state of the switches
 *			of the HEIA-FR extension board of the Beaglebone black. 
 *
 * Author: 	Daniel Gachet
 * Date: 	25.11.2018
 */

#include <am335x_gpio.h>
#include <stdbool.h>
#include "buttons.h"

// i/o pin definition --------------------------------------------------------

#define SW_GPIO		AM335X_GPIO1
#define S1_PIN	 	15
#define S2_PIN	 	16
#define S3_PIN	 	17

#define FIRST_BUTTON 	BUTTONS_1
#define NB_BUTTONS 		(BUTTONS_3 - BUTTONS_1 + 1)

static const uint32_t button[NB_BUTTONS] = {
	[BUTTONS_1] = S1_PIN,
	[BUTTONS_2] = S2_PIN,
	[BUTTONS_3] = S3_PIN,
};

static const enum buttons_states buttons_states[2][2] = {
	{BUTTONS_CLOSED,  BUTTONS_RELEASED},
	{BUTTONS_PRESSED, BUTTONS_OPEN    },
};

static bool former_state[NB_BUTTONS];

// public method implementation ----------------------------------------------

void buttons_init()
{
	// initialize gpio module
	am335x_gpio_init(SW_GPIO);

	// configure gpio pins as input 
	for (int i=FIRST_BUTTON; i<NB_BUTTONS;i++) {
		am335x_gpio_setup_pin_in(SW_GPIO, button[i], AM335X_GPIO_PULL_NONE, false);
		former_state[i] = am335x_gpio_get_state(SW_GPIO, button[i]);
	}
}

enum buttons_states buttons_get_state(enum buttons_set btn)
{
	bool new_state  = am335x_gpio_get_state(SW_GPIO, button[btn]);
	enum buttons_states state = buttons_states[former_state[btn]][new_state];
	former_state[btn] = new_state;
	return state;
}
