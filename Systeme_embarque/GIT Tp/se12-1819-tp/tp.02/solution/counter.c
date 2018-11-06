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
 * Project:	HEIA-FR / Embedded Systems 1 Laboratory
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

#include <stdio.h>
#include <stdbool.h>

#include "seg7.h"
#include "wheel.h"
#include "counter.h"

/* 7-segment: segment definition ---------------------------------------------
  
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
static const uint32_t digits[] = {
	(SEG7_A + SEG7_B + SEG7_C + SEG7_D + SEG7_E + SEG7_F  	      ), // 0
	(         SEG7_B + SEG7_C        			    			  ), // 1
    (SEG7_A + SEG7_B          + SEG7_D + SEG7_E          + SEG7_G ), // 2
    (SEG7_A + SEG7_B + SEG7_C + SEG7_D                   + SEG7_G ), // 3
    (         SEG7_B + SEG7_C                   + SEG7_F + SEG7_G ), // 4
    (SEG7_A          + SEG7_C + SEG7_D          + SEG7_F + SEG7_G ), // 5
    (SEG7_A          + SEG7_C + SEG7_D + SEG7_E + SEG7_F + SEG7_G ), // 6
    (SEG7_A + SEG7_B + SEG7_C				    				  ), // 7
    (SEG7_A + SEG7_B + SEG7_C + SEG7_D + SEG7_E + SEG7_F + SEG7_G ), // 8
    (SEG7_A + SEG7_B + SEG7_C + SEG7_D          + SEG7_F + SEG7_G ), // 9
};


// local variables -----------------------------------------------------------

static int counter =  0;


// local method implementation -----------------------------------------------

static void counter_display (int value)
{
	// test for negative values
	uint32_t dot = 0;
	if (value < 0) {
		dot = SEG7_DP1;
		value = -value;
	}

	seg7_display_dots (SEG7_RIGHT,  0);
	seg7_display_dots (SEG7_LEFT, dot);
	seg7_display_segments (SEG7_RIGHT, digits[value%10]);
	seg7_display_segments (SEG7_LEFT,  digits[(value/10)%10]);
}


// public method implementation ----------------------------------------------

void counter_init()
{
	seg7_init();
	wheel_init();
}


void counter_process()
{
	enum wheel_direction dir = wheel_get_direction();
	if (dir == WHEEL_RIGHT) {
		if (counter < 99) counter++;
	} else if (dir == WHEEL_LEFT) {
		if (counter > -99) counter--;
	}

	counter_display(counter);
}


void counter_reset()
{
	counter = 0;
}
