/*
 * seg7.c
 *
 *  Created on: Oct 1, 2018
 *      Author: sven
 */

#include <am335x_gpio.h>
#include <stdbool.h>
#include seg7.h
#include <stdio.h>

// pin definition for 7-segment access
#define GPIO0		AM335X_GPIO0
#define GPIO1	    AM335X_GPIO1
#define GPIO2		AM335X_GPIO2
#define DIG1		2
#define DIG2 		3
#define SEGA		(1<<4)
#define SEGB		(1<<5)
#define SEGC		(1<<14)
#define SEGD		(1<<22)
#define SEGE		(1<<23)
#define SEGF		(1<<26)
#define SEGG		(1<<27)
#define DP1			4
#define DP2			5

// delays
#define DELAY_ON	0x00ffff
#define DELAY_OFF	0x00ffff

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

static const struct gpio_init_7seg {
	uint32_t pin_nr;
} gpio_init_7seg[] = { { 4 },	// SEGA
		{ 5 },	// SEGB
		{ 14 },	// SEGC
		{ 22 },	// SEGD
		{ 23 },	// SEGE
		{ 26 },	// SEGF
		{ 27 },	// SEGG
		{ 4 }, { 5 } };

static const struct gpio_init_DIG {
	uint32_t pin_nr;

} gpio_init_DIG[] = { { 2 }, { 3 } };

void seg_init() {

	am335x_gpio_init(GPIO0);
	am335x_gpio_init(GPIO1);
	am335x_gpio_init(GPIO2);

	//init 7 segments
	for (uint32_t i = 0; i < ARRAY_SIZE(gpio_init_7seg); ++i) {
		am335x_gpio_setup_pin_out(GPIO0, gpio_init_7seg[i].pin_nr, false);

	}

	//init decimal point
	am335x_gpio_setup_pin_out(GPIO2, 4, false);
	am335x_gpio_change_state(GPIO2, DP1, false);
	am335x_gpio_setup_pin_out(GPIO2, 5, false);
	am335x_gpio_change_state(GPIO2, DP2, false);

	//init selectors
	for (uint32_t i = 0; i < ARRAY_SIZE(gpio_init_DIG); ++i) {
		am335x_gpio_setup_pin_out(GPIO2, gpio_init_DIG[i].pin_nr, false);
		am335x_gpio_change_state(GPIO2, gpio_init_DIG[i].pin_nr, false);
	}

}



static void delay(int value) {
	while (value > 0)
		value--;
}

static void select_display(int disp_number, bool turn_on) {

		am335x_gpio_change_state(GPIO2, disp_number, false);




}

void set_number(int numberDIG1,int numberDIG2) {

	// decoder table
	static const uint32_t array_digits[] = {
	SEGA | SEGB | SEGC | SEGD | SEGE | SEGF,            // 0
			SEGB | SEGC,                                    // 1
			SEGA | SEGB | SEGD | SEGE | SEGG,      // 2
			SEGA | SEGB | SEGC | SEGD | SEGG,      // 3
			SEGB | SEGC | SEGF | SEGG,     // 4
			SEGA | SEGC | SEGD | SEGF | SEGG,            // 5
			SEGA | SEGC | SEGD | SEGE | SEGF | SEGG,        // 6
			SEGA | SEGB | SEGC,                                    // 7
			SEGA | SEGB | SEGC | SEGD | SEGE | SEGF | SEGG,        // 8
			SEGA | SEGB | SEGC | SEGD | SEGF | SEGG,        // 9
			0 };

}

void seg7_reset()
{
	static unsigned digit = 0;
	// TURN OF ALL
	am335x_gpio_change_state(GPIO0, SEG_ALL, false);
	am335x_gpio_change_state(GPIO1, DIG_ALL, false);
	am335x_gpio_change_state(GPIO2, DP_ALL, false);

	//turn on segments for selected value
	am335x_gpio_change_state(GPIO0, display[digit].seg7, true);
	am335x_gpio_change_state(GPIO1, display[digit].digit, true);
	am335x_gpio_change_state(GPIO2, display[digit].dot, true);

	digit = (digit + 1) % 2;
}

