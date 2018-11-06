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
 * Abstract: 7-Segment Display Device Driver
 *
 * Purpose: This module implements methods to drive the segments of the two
 *   		7-segments display of the HEIA-FR extension board.
 *
 * Author: 	Daniel Gachet
 * Date: 	24.09.2018
 */

#include <stdbool.h>
#include <am335x_gpio.h>
#include "seg7.h"

// i/o pin definition for 7-segment access -----------------------------------

#define DIG_GPIO	AM335X_GPIO2
#define DIG1		(1<<2)
#define DIG2		(1<<3)
#define DIG_ALL		(DIG1 | DIG2)

#define DP_GPIO		AM335X_GPIO2
#define DP1			(1<<4)
#define DP2			(1<<5)
#define DP_ALL		(DP1 | DP2)

#define SEG_GPIO	AM335X_GPIO0
#define SEG_A		(1<<4)
#define SEG_B		(1<<5)
#define SEG_C		(1<<14)
#define SEG_D		(1<<22)
#define SEG_E		(1<<23)
#define SEG_F		(1<<26)
#define SEG_G		(1<<27)
#define SEG_ALL		(SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G)


// macro to compute number of elements of an array ---------------------------

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))


// structure to initialize gpio pins used by 7-segment -----------------------

static const struct gpio_init {
	enum am335x_gpio_modules module;
	uint32_t pin_nr;
	bool state;
} gpio_init[] = {
	{DIG_GPIO,  2, false},	// DIG1
	{DIG_GPIO,  3, false},	// DIG2

	{DP_GPIO,   4, false},	// DP1
	{DP_GPIO,   5, false},	// DP2

	{SEG_GPIO,  4, false},	// SEG_A
	{SEG_GPIO,  5, false},	// SEG_B
	{SEG_GPIO, 14, false},	// SEG_C
	{SEG_GPIO, 22, false},	// SEG_D
	{SEG_GPIO, 23, false},	// SEG_E
	{SEG_GPIO, 26, false},	// SEG_F
	{SEG_GPIO, 27, false},	// SEG_G
};


// 7-segment display: digit value --------------------------------------------

static struct digit {
	uint32_t seg7;
	uint32_t dot;
	uint32_t digit;
} display[2] = {
	[SEG7_RIGHT] = {.digit = DIG2,},
	[SEG7_LEFT]  = {.digit = DIG1,},
};


// public method implementation ----------------------------------------------

void seg7_init()
{
	// initialize gpio modules
	am335x_gpio_init(DIG_GPIO);
	am335x_gpio_init(DP_GPIO);
	am335x_gpio_init(SEG_GPIO);

	// configure gpio pins as output
	for (int i=ARRAY_SIZE(gpio_init)-1; i>=0; i--) {
		am335x_gpio_setup_pin_out(
			gpio_init[i].module, 
			gpio_init[i].pin_nr,
			gpio_init[i].state);
	}
}


void seg7_display_segments (enum seg7_display digit, uint32_t value)
{
	uint32_t segments = 0; 
	if ((value & SEG7_A) != 0) segments += SEG_A;
	if ((value & SEG7_B) != 0) segments += SEG_B;
	if ((value & SEG7_C) != 0) segments += SEG_C;
	if ((value & SEG7_D) != 0) segments += SEG_D;
	if ((value & SEG7_E) != 0) segments += SEG_E;
	if ((value & SEG7_F) != 0) segments += SEG_F;
	if ((value & SEG7_G) != 0) segments += SEG_G;
	display[digit].seg7 = segments;

}


void seg7_display_dots (enum seg7_display digit, uint32_t value)
{
	display[digit].dot = 
		((value & SEG7_DP1) ? DP1 : 0) +
		((value & SEG7_DP2) ? DP2 : 0);
}


void seg7_refresh_display()
{
	static unsigned digit = 0;

	// turn-off all segments & digits
	am335x_gpio_change_states(DIG_GPIO, DIG_ALL, false);
	am335x_gpio_change_states(DP_GPIO,  DP_ALL,  false);
	am335x_gpio_change_states(SEG_GPIO, SEG_ALL, false);

	// turn on selected segments and digits
	am335x_gpio_change_states(DP_GPIO,  display[digit].dot,   true);
	am335x_gpio_change_states(SEG_GPIO, display[digit].seg7,  true);
	am335x_gpio_change_states(DIG_GPIO, display[digit].digit, true);

	// switch to next digigt to display
	digit = (digit + 1) % ARRAY_SIZE(display);
}
