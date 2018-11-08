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
 * Project:		HEIA-FR / Embedded Systems
 *
 *
 * Author: 		Marc Roten / Sven Rouvinez
 * Date: 		Nov 5, 2018
 */
#include <stdio.h>
#include <stdbool.h>

#include "display.h"
#include "font_8x8.h"
#include "oled.h"

#define BLACK 	0
#define RED 	0xff000
#define WHITE 	0xffff



#include "thermo.h"
#include "display.h"

int main() {
//address 0x48, register 0
/*
 * thermo.h
 * display.h
 * shell.h
 * cli.h --> get tokenize
 */

	printf("START\n");

	thermo_init();
	uint8_t data[2];
	read_thermo(data);
	printf("%d\n",data[0]);

display_init();


display_circle(10,10,10,0xf800);
display_circle(10,10,5,0x58ff);
display_rectangle(5,20,0,80,0xffff);
display_rectangle(5,10,0,data[0],0xf800);


	display_init();
	display_swissFlag();

	/*
	 * background
	 */
//	display_rectangle(0,0,96,96,WHITE);
//
//	display_circle(40,40,10,BLACK);



	return 0;
}
