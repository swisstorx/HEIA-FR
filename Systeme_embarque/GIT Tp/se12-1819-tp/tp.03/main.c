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
#include "display.h"//
#include "font_8x8.h"//
#include "oled.h"//
#include "cli.h"//
#include "thermo.h"
#include "shell.h"

#define BLACK 	0
#define RED 	0xff000
#define WHITE 	0xffff

/*
 * prototypage du main
 */
void init();


#include "thermo.h"
#include "display.h"
#include <stdbool.h>

static void rotate(struct display_point* points) {
	uint32_t x1 = points->x_coor;
	points->x_coor = -points->y_coor;
	points->y_coor = x1;

}

int main() {
//address 0x48, register 0
/*
 * thermo.h
 * display.h
 * shell.h
 * cli.h --> get tokenize
 */

	printf("START\n");

	 struct display_point start_point={
			 .x_coor=55,
			 .y_coor=20
	 };
	 struct display_point end_point={
			 .x_coor=55,
			 .y_coor=80
	 };


	 struct display_point value_temperature={
			 .x_coor=55,
			 .y_coor=0,
	 };

	 display_init();
	 display_clear();
		thermo_init();



	 display_thermo_basic_form(start_point, end_point,5, 0xffff);

	 uint8_t data[2];
	 read_thermo(data);
	 while(true){

		 read_thermo(data);

		 value_temperature.y_coor=(end_point.y_coor/2)+data[0];

		 display_rectangle(start_point,value_temperature,0xf567);
	 }


 start_point.x_coor = 55;
 start_point.y_coor = 20;


 end_point.x_coor = 55;
 end_point.y_coor = 80;


 display_init();
 display_clear();

 display_thermo_basic_form(start_point, end_point, 5, WHITE);c3
	while(1) {
		cli_probe();
	}
}
/*
 * initialise tous nos .c
 */
void init(){
	display_init();
	oled_init(100);
	cli_init();
	shell_init();
}








