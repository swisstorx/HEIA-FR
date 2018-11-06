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
 * Abstract: Serpentine application
 *
 * Purpose: This module implements a serpentine over the 7-segment display.
 *          The LEDs of the 7-segment display will be turn on/off according 
 *          to the rotations of the rotary encoder. 
 *
 * Author: 	Daniel Gachet
 * Date: 	24.09.2018
 */

#include <stdio.h>
#include <stdbool.h>

#include "seg7.h"
#include "wheel.h"
#include "serpentine.h"

// macro to compute number of elements of an array ---------------------------

#define ARRAY_SIZE(x) ((signed)(sizeof(x) / sizeof(x[0])))


// serpentine ----------------------------------------------------------------

static const struct serpentine {
	uint32_t left;
	uint32_t right;
} serpentine [] = {
	{SEG7_A, 0	    },
	{SEG7_B, 0	    },
	{0,      SEG7_G	},
	{0,      SEG7_B	},
	{0,      SEG7_A	},
	{0,      SEG7_F	},
	{0,      SEG7_E	},
	{0,      SEG7_D	},
	{0,      SEG7_C	},
	{0,      SEG7_G	},
	{SEG7_G, 0		},
	{SEG7_E, 0		},
	{SEG7_D, 0		},
	{SEG7_C, 0		},
	{SEG7_G, 0		},
	{SEG7_F, 0		},
};


// local variables -----------------------------------------------------------

static signed counter =  0;


// local method implementation -----------------------------------------------

static void serpentine_display (unsigned value)
{
	value = value % ARRAY_SIZE(serpentine);

	seg7_display_dots (SEG7_LEFT,  0);
	seg7_display_dots (SEG7_RIGHT, 0);
	seg7_display_segments (SEG7_LEFT,  serpentine[value].left);
	seg7_display_segments (SEG7_RIGHT, serpentine[value].right);
}


// public method implementation ----------------------------------------------

void serpentine_init()
{
	seg7_init();
	wheel_init();
}


void serpentine_process()
{
	enum wheel_direction dir = wheel_get_direction();
	if (dir == WHEEL_RIGHT) {
		counter++;
		if (counter > ARRAY_SIZE(serpentine)) {
			counter -= ARRAY_SIZE(serpentine);
		}
	} else if (dir == WHEEL_LEFT) {
		counter--;
		if (counter < 0) {
			counter += ARRAY_SIZE(serpentine);
		}
	}

	serpentine_display(counter);
}


void serpentine_reset()
{
	counter = 0;
}

