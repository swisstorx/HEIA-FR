#pragma once
#ifndef SERPENTINE_H
#define SERPENTINE_H
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
 * Abstract: Serpentine application
 *
 * Purpose: This module implements a serpentine over the 7-segment display.
 *          The LEDs of the 7-segment display will be turn on/off according 
 *          to the rotations of the rotary encoder. 
 *
 * Author: 	Daniel Gachet
 * Date: 	24.09.2018
 */


/**
 * method to initialize the resoures of the serpentine module.
 */
extern void serpentine_init();


/**
 * calling this method provides a time slice to the serpentine's 
 * application for its processing
 */
extern void serpentine_process();


/**
 * method to force initial state
 */
extern void serpentine_reset();

#endif