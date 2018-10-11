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
 * Project:		HEIA-FR / Embedded Systems 1 Laboratory
 *
 * Abstract:	Introduction the ARM's assembler language
 *
 * Purpose:		First step in C and remote target debugging...
 * 				Program to show a short message on the 7-segment display
 *
 * Author: 		<authors>
 * Date: 		<date>
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <am335x_gpio.h>

// -- constants & variable declaration ---------------------------------------

// delays
#define DELAY_ON	0x06ffff
#define DELAY_OFF	0x00ffff

// pin definition for 7-segment access
#define GPIO2		AM335X_GPIO2
#define DIG1		(1<<2)
#define GPIO0		AM335X_GPIO0
#define SEGA		(1<<4)
#define SEGB		(1<<5)
#define SEGC		(1<<14)
#define SEGD		(1<<22)
#define SEGE		(1<<23)
#define SEGF		(1<<26)
#define SEGG		(1<<27)
#define S1			(1<<15)
#define S2			(1<<16)
#define S3			(1<<17)

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
	uint32_t pin_nr;
} gpio_init[] = {
	{ 4},	// SEGA
	{ 5},	// SEGB
	{14},	// SEGC
	{22},	// SEGD
	{23},	// SEGE
	{26},	// SEGF
	{27},	// SEGG
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
								SEGE | SEGF       , //I
	SEGA | SEGB | SEGC | 	   SEGE | SEGF | SEGG , //A
											 SEGG, //-
	SEGA |                     SEGE | SEGF | SEGG, //F
							   SEGE		   | SEGG , //r

	0 
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
 * method to turn on/off a set of LED
 * @param leds set of LED
 * @param on state (true --> on, false--> 0ff)
 */
static void turn_leds_on(uint32_t leds, bool on)
{
	if (on)
		am335x_gpio_change_states(GPIO0, leds, true);
	else
		am335x_gpio_change_states(GPIO0, leds, false);
}

/**
 * method to switch LED on and off
 * @param leds set of LED
 */
void switch_leds_on_off (uint32_t leds)
{
	turn_leds_on(leds, true);
	delay(DELAY_ON);

	turn_leds_on(leds, false);
	delay(DELAY_OFF);
}

//-- implementation of public methods ---------------------------------------

int main()
{
	// display banner on the console
	printf ("%s", banner);

	// configure gpio pins as output
	am335x_gpio_init(GPIO2);
	am335x_gpio_setup_pin_out(GPIO2, 2, true);

	am335x_gpio_init(GPIO0);
	for (int i=ARRAY_SIZE(gpio_init)-1; i>=0; i--) {
		am335x_gpio_setup_pin_out(GPIO0, gpio_init[i].pin_nr, false);

	}

	// main loop
	while(true) {
		const uint32_t* lut = &msg[0];
		while(true) {
			long leds = *lut++;
			if (leds == 0) break;
			switch_leds_on_off(leds);
		}
	}

	return 0;
}
