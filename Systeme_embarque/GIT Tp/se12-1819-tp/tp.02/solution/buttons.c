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
 * Date: 	24.09.2018
 */

#include <am335x_gpio.h>
#include "buttons.h"

// i/o pin definition --------------------------------------------------------

#define SW_GPIO		AM335X_GPIO1
#define S1_PIN	 	15
#define S2_PIN	 	16
#define S3_PIN	 	17

#define MASK		(BUTTONS_1 | BUTTONS_2 | BUTTONS_3)
#define SHIFT		S1_PIN


// public method implementation ----------------------------------------------

void buttons_init()
{
	// initialize gpio module
	am335x_gpio_init(SW_GPIO);

	// configure gpio pins as input 
	am335x_gpio_setup_pin_in(SW_GPIO, S1_PIN, AM335X_GPIO_PULL_NONE, false);
	am335x_gpio_setup_pin_in(SW_GPIO, S2_PIN, AM335X_GPIO_PULL_NONE, false);
	am335x_gpio_setup_pin_in(SW_GPIO, S3_PIN, AM335X_GPIO_PULL_NONE, false);
}

uint32_t buttons_get_state()
{
	uint32_t state = am335x_gpio_get_states (SW_GPIO);

	// invert button state due to high level logic
	return ~(state >> SHIFT) & MASK;
}
