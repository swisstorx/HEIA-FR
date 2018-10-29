/*
 * serpent.c
 *
 *  Created on: Oct 1, 2018
 *      Author: sven
 *      Modified : Marc
 */

#include <stdio.h>
#include <am335x_gpio.h>
#include "serpent.h"

#define CHA 		1
#define CHB 		29

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
#define SEG_ALL		(SEGA | SEGB | SEGC | SEGD | SEGE | SEGF | SEGG)
#define DP1			4
#define DP2			5

#define ARRAY_SIZE sizeof(array_digits)/sizeof(array_digits[0])
static const uint32_t array_digits[] = {
SEGG,
SEGB,
SEGA,
SEGF,
SEGE,
SEGD,
SEGC, 0 };

static bool changed = false;

void displaySnake(int snakeState,bool value_changed) {

	am335x_gpio_change_state(GPIO2, DIG1, false);
	am335x_gpio_change_state(GPIO2, DIG2, false);
	am335x_gpio_change_states(GPIO0, SEG_ALL, false);

	//value_changed it's for update the changed if the wheel has been turned
	if (((uint32_t)snakeState >= (ARRAY_SIZE-2) )&& value_changed) {
		changed = !changed;
		snakeState = 6;

	}else if (snakeState <= 0 && value_changed) {
		changed = !changed;
		snakeState = 0;
	}

	if(snakeState < 0) snakeState=0;
	am335x_gpio_change_state(GPIO2, DIG1, changed);
	am335x_gpio_change_state(GPIO2, DIG2, !changed);
	am335x_gpio_change_states(GPIO0, array_digits[snakeState], true);
}

uint32_t get_size_path(){
	//-1 because 0 doesn't count
	return ARRAY_SIZE-1;
}

