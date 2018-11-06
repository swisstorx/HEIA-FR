#pragma once
#ifndef LEDS_H
#define LEDS_H
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
 * Project: HEIA-FR / Embedded Systems 1 Laboratory
 *
 * Abstract: LED Device Driver
 *
 * Purpose: This module implements a method to control state of the LEDs
 *		    of the HEIA-FR extension board of the Beaglebone black. 
 *
 * Author: 	Daniel Gachet
 * Date: 	24.09.2018
 */

#include <stdint.h>

/* enumaration of available leds */
enum leds_set {
    LEDS_1 = (1<<0),
    LEDS_2 = (1<<1),
    LEDS_3 = (1<<2),
};

/**
 * method to initialize the resoures of the LED
 * this method shall be called prior any other.
 */
extern void leds_init();

/**
 * method to get state of the 3 LED.
 * 
 * @return state of the available LED (LED in set ==> LED is on)
 */
extern uint32_t leds_get_state();

/**
 * method to set state of the 3 LED.
 * 
 * @param state state of the available LED (LED in state ==> turn on the LED)
 */
extern void leds_set_state(uint32_t state);

#endif