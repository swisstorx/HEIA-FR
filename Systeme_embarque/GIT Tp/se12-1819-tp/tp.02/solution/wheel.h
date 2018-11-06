#pragma once
#ifndef WHEEL_H
#define WHEEL_H
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
 * Abstract: Wheel Device Driver
 *
 * Purpose:	This module provide an interface to get the direction of rotation of
 *          the wheel populated on the HEIA-FR extension board of the Beaglebone. 
 *
 * Author: 	Daniel Gachet
 * Date: 	24.09.2018
 */

#include <stdint.h>

/**
 * wheel rotation directions
 */
enum wheel_direction {WHEEL_STILL, WHEEL_RIGHT, WHEEL_LEFT};


/**
 * method to initialize the resoures of the wheel
 * this method shall be called prior any other.
 */
extern void wheel_init();


/**
 * method to get the direction of rotation of the encoder
 * 
 * @return direction of rotation 
 */
extern enum wheel_direction wheel_get_direction();

#endif
