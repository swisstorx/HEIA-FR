#pragma once
#ifndef COUNTER_H
#define COUNTER_H
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
 * Abstract: Counter application
 *
 * Purpose: This module implements a counter [-99...99] over the 7-segment 
 *          display. According to rotations of the rotary encoder, the counter
 *          will be incremented (rotation to the right) or decremented 
 *          (rotation to the left). The LEDs of the 7-segment display will 
 *          be turn on/off according to the counter value. 
 *
 * Author: 	Daniel Gachet
 * Date: 	24.09.2018
 */


/**
 * method to initialize the resoures of the counter module.
 */
extern void counter_init();


/**
 * calling this method provides a time slice to the counter's 
 * application for its processing
 */
extern void counter_process();


/**
 * method to force initial state
 */
extern void counter_reset();

#endif