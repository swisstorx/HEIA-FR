#pragma once
#ifndef BUTTONS_H
#define BUTTONS_H
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
 * Abstract: Press Buttons Device Driver
 *
 * Purpose: This module implements a method to get state of the press
 *		    buttons of the HEIA-FR extension board of the Beaglebone black. 
 *
 * Author: 	Daniel Gachet
 * Date: 	24.09.2018
 */

#include <stdint.h>

/* enumation of possible button states */
enum buttons_states {
    BUTTONS_OPEN, 
    BUTTONS_CLOSED, 
    BUTTONS_PRESSED, 
    BUTTONS_RELEASED
};

/* enumaration of available buttons */
enum buttons_set {
    BUTTONS_1,
    BUTTONS_2,
    BUTTONS_3,
};


/**
 * method to initialize the resoures of the press buttons
 * this method shall be called prior any other.
 */
extern void buttons_init();


/**
 * method to get state of specified buttons
 * 
 * @param btn button number
 * @return current button state
 */
extern enum buttons_states buttons_get_state(enum buttons_set btn);

#endif
