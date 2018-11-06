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
 * Abstract: Wheel Device Driver
 *
 * Purpose:	This module provide an interface to get the direction of rotation of
 *          the wheel populated on the HEIA-FR extension board of the Beaglebone. 
 *
 * Author: 	Daniel Gachet
 * Date: 	24.09.2018
 */

#include <am335x_gpio.h>
#include "wheel.h"

// i/o pin definition
#define CHA_GPIO	AM335X_GPIO2
#define CHA_PIN	 	1
#define CHB_GPIO	AM335X_GPIO1
#define CHB_PIN	 	29

// rotary encoder finite state machine based on former and new state ---------
static const enum wheel_direction transitions[4][4] = {
	{ WHEEL_STILL, WHEEL_STILL,  WHEEL_STILL,  WHEEL_STILL },
	{ WHEEL_LEFT,  WHEEL_STILL,  WHEEL_STILL,  WHEEL_RIGHT },
	{ WHEEL_RIGHT, WHEEL_STILL,  WHEEL_STILL,  WHEEL_LEFT  },
	{ WHEEL_STILL, WHEEL_STILL,  WHEEL_STILL,  WHEEL_STILL }
};

// local variables -----------------------------------------------------------

static int former_state = 0;

// local method implementation -----------------------------------------------

static inline int get_encoder_state()
{
	int state = 0;
	if (am335x_gpio_get_state (CHA_GPIO, CHA_PIN)) state += 1;
	if (am335x_gpio_get_state (CHB_GPIO, CHB_PIN)) state += 2;
	return state;
}

// debug method implementation ----------------------------------------------

#define SZ 10000
static enum wheel_direction wheel_hist_buf[SZ];
static void update_history(enum wheel_direction dir)
{
	static enum wheel_direction old = WHEEL_STILL;
	static int in = 0;
	if ((dir != WHEEL_STILL)) {
		wheel_hist_buf[in++] = (old == WHEEL_STILL) ? dir : (dir << 3) + old;
		if (in >= SZ) in = 0;
	}
	old = dir;
}

// public method implementation ----------------------------------------------

void wheel_init()
{
	// initialize gpio module
	am335x_gpio_init(CHA_GPIO);
	am335x_gpio_init(CHB_GPIO);

	// configure gpio pins as output 
	am335x_gpio_setup_pin_in(CHA_GPIO, CHA_PIN, AM335X_GPIO_PULL_NONE, true);
	am335x_gpio_setup_pin_in(CHB_GPIO, CHB_PIN, AM335X_GPIO_PULL_NONE, true);

	former_state = get_encoder_state();
}

enum wheel_direction wheel_get_direction()
{
	int state = get_encoder_state();
	enum wheel_direction dir = transitions[former_state][state];
	former_state = state;

	update_history(dir);

	return dir;
}
