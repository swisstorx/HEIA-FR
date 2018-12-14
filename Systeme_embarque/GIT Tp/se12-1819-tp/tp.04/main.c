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
 <<<<<<< HEAD
 * Project:		HEIA-FR / Embedded Systems
 *
 *
 * Author: 		Marc Roten / Sven Rouvinez
 * Date: 		3 Dec 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "timer.h"
#include "buttons.h"
#include "display.h"
#include "oled.h"

#define MAX_VALUE_TIMER 60000000			//2500"24'000'000*10⁻3 = 60000000
#define MIN_VALUE_TIMER 12000000			//500 = 60000000/5 = 12000000



#define BLACK   0
#define RED 	0xff000
#define WHITE 	0xfffff
#define GREEN   0x00cc0
#define ORANGE	0xFC000
#define UNIT_TIME 1000

#define S1			(15)
#define S2			(16)
#define S3		    (17)

enum states {
	IDLE, PRESSED, ERROR, RELEASED, SCORE,
};

uint32_t random_time() {
	rand();
	return random() % (MAX_VALUE_TIMER + 1 - MIN_VALUE_TIMER) + MIN_VALUE_TIMER;
}


void delay(int value){

	while (value > 0) value--;
}

void init() {

	button_init();
	display_init();
}

int main() {
	init();
	uint32_t rand = 0;

	enum states state = IDLE;
	uint32_t resTime = 0;
	uint32_t timerReact = 0;
	double displayTime = 0;

	while (1) {

		switch (state) {
		case IDLE:

			display_string(0, 72, "ready", WHITE, BLACK);

			rand = random_time();
			if (button_s2_is_pressed()) { //cas ou on presse le bouton 2
				display_clear();
				display_string(0, 60, "GET READY", ORANGE, BLACK);
				state = PRESSED;
				dmtimer1_init(DMTIMER2);
				dmtimer1_init(DMTIMER3);
			}
			break;
		case PRESSED:

			if (button_s2_is_pressed()) {
				display_string(0, 60, "GET READY", ORANGE, BLACK);
				while ((timerReact = dmtimer1_get_counter(DMTIMER2)) < rand) {

					if (!button_s2_is_pressed()) {

						state = ERROR;
						break;
					}

				}
				state = RELEASED;
				break;

			}else{
				state = ERROR;
			}
			break;
		case ERROR:
			while(!button_s2_is_pressed()) {
				display_string(24, 72, "ERROR", RED, BLACK);
			}
			state = IDLE;
			display_clear();

			break;
		case RELEASED:			//affiche le moment ou le joueur se retire

			while (button_s2_is_pressed()) {
				display_string(0, 60, "RELEASE NOW", GREEN, BLACK);
				resTime = dmtimer1_get_counter(DMTIMER3) - timerReact;
			}
			state = SCORE;

			break;
		case SCORE:
			printf("\n"); // do not remove - bug in C https://stackoverflow.com/questions/8560734/error-a-label-can-only-be-part-of-a-statement
			char myResString[72];

			displayTime = ((double) resTime / dmtimer1_get_frequency())*UNIT_TIME;

			sprintf(myResString, "%d ms", (int)displayTime ); //(passage secondes à milisecondes)


			while(!button_s2_is_pressed()){
				display_string(0, 24, "react time", RED, BLACK);
				display_string(0, 16, myResString, RED, BLACK);
			}
			display_clear();
			state = IDLE;

			break;
		default:
			state = IDLE;
			break;
		}
	}

	return 0;
}
;
