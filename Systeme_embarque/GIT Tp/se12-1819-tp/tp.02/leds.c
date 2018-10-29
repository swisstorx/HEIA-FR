/*
 * leds.c
 *
 *  Created on: Oct 1, 2018
 *      Author: sven
 *      Modified: Marc
 */

#include <am335x_gpio.h>
#include <stdio.h>

#define LED1 (12)
#define LED2 (13)
#define LED3 (14)
#define GPIO1 AM335X_GPIO1

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

static const struct gpio_init_leds {
	uint32_t pin_nr;
} gpio_init_leds[] = { {LED1} ,{LED2} ,  {LED3} };

void leds_init() {
	am335x_gpio_init(GPIO1);
	for (uint32_t i = 0; i < ARRAY_SIZE(gpio_init_leds); ++i) {
		am335x_gpio_setup_pin_out(GPIO1, gpio_init_leds[i].pin_nr, false);
		am335x_gpio_change_state(GPIO1,gpio_init_leds[i].pin_nr,false);
	}
}

void set_state_by_led(int pin_led,bool state) {
  am335x_gpio_change_state(GPIO1,pin_led,state);
}
