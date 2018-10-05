/*
 * seg7.c
 *
 *  Created on: Oct 1, 2018
 *      Author: sven
 */

#include <am335x_gpio.h>
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
#define DELAY_ON	0x06ffff
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

void init_7seg() {

	am335x_gpio_init(GPIO0);
	am335x_gpio_init(GPIO1);
	am335x_gpio_init(GPIO2);

	//init 7 segments
	for (int i = 0; i < ARRAY_SIZE(gpio_init_7seg); ++i) {
		am335x_gpio_setup_pin_out(GPIO0, gpio_init_7seg[i].pin_nr, false);

	}

	//init decimal point
	am335x_gpio_setup_pin_out(GPIO2, 4, false);
	am335x_gpio_change_state(GPIO2, DP1, false);
	am335x_gpio_setup_pin_out(GPIO2, 5, false);
	am335x_gpio_change_state(GPIO2, DP2, false);

	//init selectors
	for (int i = 0; i < ARRAY_SIZE(gpio_init_DIG); ++i) {
		am335x_gpio_setup_pin_out(GPIO2, gpio_init_DIG[i].pin_nr, false);
		am335x_gpio_change_state(GPIO2, gpio_init_DIG[i].pin_nr, false);
	}

}

static void select_display(int disp_number, bool turn_on) {
	am335x_gpio_change_state(GPIO2, disp_number, turn_on);
}

static void delay(int value) {
	while (value > 0)
		value--;
}

void set_number(int number) {

	//static const uint32_t msg_DIG2[] = { };
	// message to display: lookup table (null terminated)
	/*static const uint32_t msg[] = {
	 SEGB | SEGC | SEGE | SEGF | SEGG, // H
	 SEGA | SEGD | SEGE | SEGF | SEGG, // E
	 SEGE | SEGF, //I
	 SEGA | SEGB | SEGC | SEGE | SEGF | SEGG, //A
	 SEGG, //-
	 SEGA | SEGE | SEGF | SEGG, //F
	 SEGE | SEGG, //r

	 0 };
	 */

	static const uint32_t msg_DIG1[] = {
	SEGA | SEGB | SEGC | SEGD | SEGE | SEGF,
	SEGB | SEGC | SEGD | SEGE | SEGF


	};



	while (true) {

		select_display(DIG1, true);
		delay(DELAY_ON);
		select_display(DIG1, false);
		select_display(DIG2, true);
		delay(DELAY_ON);
		select_display(DIG2, false);

	}

	if (number < 10) {

		static const uint32_t msg_DIG1[] = { SEGA | SEGB | SEGC | SEGD | SEGE
				| SEGF, 0 };

		am335x_gpio_change_states(GPIO1, msg_DIG1[0], true);

	}

	if (number < 0) {
		am335x_gpio_change_state(GPIO1, DP1, true);
	}

	if (number > 99 || number < -99) {
		static const uint32_t msg_DIG1[] = { SEGA | SEGB | SEGD | SEGE | SEGF
				| SEGG, 0 };
	}
}

