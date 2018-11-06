#pragma once
#ifndef SEG7_H
#define SEG7_H
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
 * Abstract: 7-Segment Display Device Driver
 *
 * Purpose: This module implements methods to drive the segments of the two
 *   		7-segments display of the HEIA-FR extension board.
 *
 * Author: 	Daniel Gachet
 * Date: 	24.09.2018
 */

#include <stdint.h>


/* 7-segment: diplays */
enum seg7_display {
    SEG7_RIGHT,
    SEG7_LEFT,
};

/* 7-segment: segment definition

    DP1 o  +----(A)----+
           |           |
          (F)          (B)
           |           |
           +----(G)----+
           |           |
          (E)         (C)
           |           |
           +----(D)----+ o DP2
*/

/* list of available segments, could be used as a set of segments */
enum seg7_segments {
    SEG7_A = (1<<0),
    SEG7_B = (1<<1),
    SEG7_C = (1<<2),
    SEG7_D = (1<<3),
    SEG7_E = (1<<4),
    SEG7_F = (1<<5),
    SEG7_G = (1<<6),
};

/* list of available dots, could be used as a set of points */
enum seg7_dots {
    SEG7_DP1 = (1<<0),
    SEG7_DP2 = (1<<1),
};

/**
 * method to initialize the resoures of the 7-segment display
 * this method shall be called prior any other.
 */
extern void seg7_init();


/**
 * method to turn on a set of dots of the the 7-segments display
 * only the specified dots will be turned on
 * 
 * @param value set of dots to turn on 
 * @param digit 7-segments display digit number (right or left)
 */
extern void seg7_display_dots (enum seg7_display digit, uint32_t value);


/**
 * method to turn on a set of segments of the the 7-segments display
 * only the specified segments will be turned on
 * 
 * @param value set of segments to turn on 
 * @param digit 7-segments display digit number (right or left)
 */
extern void seg7_display_segments (enum seg7_display digit, uint32_t value);


/**
 * method to refresh the 7-segment display
 */
extern void seg7_refresh_display();

#endif
