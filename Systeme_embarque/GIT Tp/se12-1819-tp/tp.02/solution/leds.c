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
 * Abstract: LED Device Driver
 *
 * Purpose:	This module implements a method to control state of the LED
 *			of the HEIA-FR extension board of the Beaglebone black. 
 *
 * Author: 	Daniel Gachet
 * Date: 	24.09.2018
 */

#include <am335x_gpio.h>
#include "leds.h"

// pin definition
#define LED_GPIO	AM335X_GPIO1
#define LED1_PIN	12
#define LED2_PIN	13
#define LED3_PIN	14

#define MASK		(LEDS_1 | LEDS_2 | LEDS_3)
#define SHIFT		LED1_PIN

void leds_init()
{
	// initialize gpio module
	am335x_gpio_init(LED_GPIO);

	// configure gpio pins as output 
	am335x_gpio_setup_pin_out(LED_GPIO, LED1_PIN, false);
	am335x_gpio_setup_pin_out(LED_GPIO, LED2_PIN, false);
	am335x_gpio_setup_pin_out(LED_GPIO, LED3_PIN, false);

}

uint32_t leds_get_state()
{
	uint32_t state = am335x_gpio_get_states (LED_GPIO);
	return (state >> SHIFT) & MASK;
}

void leds_set_state(uint32_t state)
{
	am335x_gpio_change_states(LED_GPIO, (~state & MASK) << SHIFT, false);
	am335x_gpio_change_states(LED_GPIO, ( state & MASK) << SHIFT, true);
}
