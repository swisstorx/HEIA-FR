/*
 * seg7.c
 *
 *  Created on: Oct 1, 2018
 *      Author: sven
 *      Modified: Marc
 */

#include <am335x_gpio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

struct digit {
	int d1;
	int d2;
	bool negative;
};

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

static uint32_t digit1;
static uint32_t digit2;
static bool dp;

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

static struct digit split_number(int number) {

	int number_nABS = number;

	number = abs(number);

	struct digit digit_to_print = { number / 10, number % 10, false };

	if (number_nABS < 0)
		digit_to_print.negative = true;
	else
		digit_to_print.negative = false;

	return digit_to_print;
}

void refresh_display() {

	static unsigned digit = 0;
	//switch between dig
	digit = (digit + 1) % 2;

	am335x_gpio_change_states(GPIO0, array_digits[8], false);
	am335x_gpio_change_state(GPIO2, DP1, false);

	switch (digit) {
	//turn on dig1
	case 0:

		am335x_gpio_change_state(GPIO2, DIG2, false);
		am335x_gpio_change_state(GPIO2, DIG1, true);
		am335x_gpio_change_states(GPIO0, digit1, true);

		if (dp)
			am335x_gpio_change_state(GPIO2, DP1, true);

		break;

		//turn on dig2
	case 1:

		am335x_gpio_change_state(GPIO2, DIG1, false);
		am335x_gpio_change_state(GPIO2, DIG2, true);
		am335x_gpio_change_states(GPIO0, digit2, true);
		break;
	}
}

void set_number(int number) {

	struct digit number_splitted = split_number(number);

	if (abs(number) < 10)
		number_splitted.d1 = 0;

	digit1 = array_digits[number_splitted.d1];
	digit2 = array_digits[number_splitted.d2];
	dp = number_splitted.negative;

	refresh_display();

}

