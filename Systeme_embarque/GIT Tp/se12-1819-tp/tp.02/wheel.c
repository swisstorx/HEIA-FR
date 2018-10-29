/*
 * wheel.c
 *
 *  Created on: Oct 1, 2018
 *      Author: sven
 *      Modified : Marc
 *
 */
#include <stdio.h>
#include <am335x_gpio.h>

#define CHA 		1
#define GPIO2 		AM335X_GPIO2
#define CHB 		29
#define GPIO1 		AM335X_GPIO1
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

enum wheel_direction {
	WHEEL_STILL, WHEEL_RIGHT, WHEEL_LEFT
};

//synthèse de la machine d'état
static const enum wheel_direction transitions[4][4] = { { WHEEL_STILL,
		WHEEL_STILL, WHEEL_STILL, WHEEL_STILL }, { WHEEL_LEFT, WHEEL_STILL,
		WHEEL_STILL, WHEEL_RIGHT }, { WHEEL_RIGHT, WHEEL_STILL, WHEEL_STILL,
		WHEEL_LEFT }, { WHEEL_STILL, WHEEL_STILL, WHEEL_STILL, WHEEL_STILL } };

static int former_state = 0;

static inline int get_encoder_state() {
	int state = 0;
	if (am335x_gpio_get_state(GPIO2, CHA))
		state += 1;
	if (am335x_gpio_get_state(GPIO1, CHB))
		state += 2;

	return state;
}

void wheel_init() {
	am335x_gpio_init(GPIO1);
	am335x_gpio_init(GPIO2);

	am335x_gpio_setup_pin_in(GPIO1, CHB, AM335X_GPIO_PULL_NONE, true);
	am335x_gpio_setup_pin_in(GPIO2, CHA, AM335X_GPIO_PULL_NONE, true);

	former_state = get_encoder_state();

}

enum wheel_direction get_wheel_direction() {
	int state = get_encoder_state();

	//controle si la direction à changé depuis le dernier contrôle
	enum wheel_direction direction = transitions[former_state][state];

	former_state = state;

	return direction;
}

