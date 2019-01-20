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
 * Abstract: Introduction to the assembly programming language
 *
 * Purpose:	Game tower of hanoi.
 *
 * Author: 	Daniel Gachet
 * Date: 	10.12.2018
 */

#include <stdio.h>

#include "buttons.h"
#include "tower_of_hanoi.h"

int main()
{
	// print program banner
	printf ("HEIA-FR - Embedded Systems 1 Laboratory\n"
			"Tower of Hanoi - An introduction to the assembly programming language\n");

	// initialization 
	buttons_init();


	int from = 0;
	int to = 0;
	tower_of_hanoi_init(from);


	while(1) {
		if (buttons_get_state(BUTTONS_1)==BUTTONS_PRESSED) to = 0; 
		if (buttons_get_state(BUTTONS_2)==BUTTONS_PRESSED) to = 1; 
		if (buttons_get_state(BUTTONS_3)==BUTTONS_PRESSED) to = 2; 

		if (to != from) {
			uint32_t x = ~((1<<from) | (1<<to)) & 0x7;
			int by = x == 1 ? 0 : x == 2 ? 1 : 2;

			tower_of_hanoi_move(from, to, by, tower_of_hanoi_disks());
			from = to;
		}
	}
	return 0;
}
