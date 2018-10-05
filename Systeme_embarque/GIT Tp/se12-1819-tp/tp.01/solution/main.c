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
 * Abstract: Introduction the ARM's assembler language
 *
 * Purpose:	First step in C and remote target debugging...
 * 			Program to show a short message on the 7-segment display
 *
 * Author: 	Daniel Gachet
 * Date: 	14.09.2018
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <am335x_gpio.h>

// -- constants & variable declaration ---------------------------------------

// delays
#define DELAY_ON	0x05ffff
#define DELAY_OFF	0x00ffff

// pin definition for 7-segment access
#define DIG_GPIO	AM335X_GPIO2
#define DIG1		(1<<2)

#define SEG_GPIO	AM335X_GPIO0
#define SEGA		(1<<4)
#define SEGB		(1<<5)
#define SEGC		(1<<14)
#define SEGD		(1<<22)
#define SEGE		(1<<23)
#define SEGF		(1<<26)
#define SEGG		(1<<27)

// macro to compute number of elements of an array
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

/* structure to initialize gpio pins used by 7-segment
   segment definition

           +-- SEG_A --+
           |           |
         SEG_F       SEG_B
           |           |
           +-- SEG_G --+
           |           |
         SEG_E       SEG_C
           |           |
           +-- SEG_D --+
*/
static const struct gpio_init {
	enum am335x_gpio_modules module;
	uint32_t pin_nr;
	bool state;
} gpio_init[] = {
	{DIG_GPIO,  2, true },	// DIG1
	{SEG_GPIO,  4, false},	// SEGA
	{SEG_GPIO,  5, false},	// SEGB
	{SEG_GPIO, 14, false},	// SEGC
	{SEG_GPIO, 22, false},	// SEGD
	{SEG_GPIO, 23, false},	// SEGE
	{SEG_GPIO, 26, false},	// SEGF
	{SEG_GPIO, 27, false},	// SEGG
};

// String definition used for message outputs (printf)
static const char* banner =  
	"\n"
	"HEIA-FR - Embedded Systems 1 Laboratory\n"
	"First step in C and remote target debugging\n"
	"--> display a simple message on the 7-segment display\n"
	"\n";

// message to display: lookup table (null terminated)
static const uint32_t msg[]	= {
	       SEGB | SEGC |        SEGE | SEGF | SEGG, // H
	SEGA |               SEGD | SEGE | SEGF | SEGG, // E
	                            SEGE | SEGF       , // I
	SEGA | SEGB | SEGC |        SEGE | SEGF | SEGG, // A
	                                          SEGG, // -
	SEGA |                      SEGE | SEGF | SEGG, // F
	                            SEGE |        SEGG, // r
};

// -- implementation of local methods ----------------------------------------

/**
 * method to delay for a given time
 * @param value delay
 */
static void delay(int value)
{
	while (value > 0) value--;
}

/**
 * method to display a character on the 7-segment for a given period of time
 * @param leds set of LED
 */
void display_char (uint32_t leds)
{
	am335x_gpio_change_states(SEG_GPIO, leds, true);
	delay(DELAY_ON);

	am335x_gpio_change_states(SEG_GPIO, leds, false);
	delay(DELAY_OFF);
}

//-- implementation of public methods ---------------------------------------

int main()
{
	// display banner on the console
	printf ("%s", banner);

	// configure gpio pins as output
	am335x_gpio_init(DIG_GPIO);
	am335x_gpio_init(SEG_GPIO);
	for (int i=ARRAY_SIZE(gpio_init)-1; i>=0; i--) {
		am335x_gpio_setup_pin_out(
			gpio_init[i].module, 
			gpio_init[i].pin_nr, 
			gpio_init[i].state);
	}

	// main loop
	while(true) {
		for (unsigned i=0; i < ARRAY_SIZE(msg); i++) {
			display_char(msg[i]);
		}
	}

	return 0;
}
