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
 * Project:	HEIA-FR / Embedded Systems 2 Laboratory
 *
 * Abstract: display
 *
 * Purpose:
 *
 * Origin:
 *
 * Author: 	Sven Rouvinez / Marc Roten
 * Date: 	09.12.2018
 */
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "thermo.h"
#include "oled.h"
#include "font_8x8.h"
#include "display.h"

#define SCREEN_WIDTH 96
#define SCREEN_HEIGHT 96
#define BLACK 0

static int scale;
static bool thermo_initialized = false;
static bool color_initialized = false;
static int minValue, maxValue;
static int thermo_side, minColor, actColor, maxColor;

void display_init() {
	oled_init(OLED_V100);
	display_clear();
}

void display_clear() {
	oled_init(OLED_V100);
	oled_memory_size(0, SCREEN_WIDTH - 1, 0, SCREEN_HEIGHT);
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
		oled_color(BLACK);
	}
}

extern void display_rect(struct display_point bottom_left,
		struct display_point top_right, uint32_t color) {
	oled_memory_size(bottom_left.x_coor, top_right.x_coor, bottom_left.y_coor,
			top_right.y_coor);
	for (uint32_t i = 0; i < top_right.x_coor * top_right.y_coor; i++) {
		oled_color(color);
	}
}

void display_circle(struct display_circle circle) {
	for (int i = -circle.radius; i <= (int) circle.radius; i++) {
		int a = sqrt(circle.radius * circle.radius - i * i);
		oled_memory_size(circle.y_coor - a, circle.y_coor + a,
				(96 - 1 - (circle.x_coor + i)), (96 - 1 - (circle.x_coor + i)));
		for (unsigned int j = 2 * a; j > 0; j--) {
			oled_color(circle.color);
		}
	}
}

extern void display_line(struct display_point start, int size,
		bool isHorizontal, uint32_t color) {
	if (isHorizontal) {
		oled_memory_size(start.x_coor, start.x_coor, start.y_coor,
				start.y_coor + size);
	} else {
		oled_memory_size(start.x_coor - size, start.x_coor, start.y_coor,
				start.y_coor);
	}
	for (int i = 0; i <= size; i++) {
		oled_color(color);
	}
}

extern void display_thermo_basic_form() {
	int32_t ray = 5;
	struct display_point center_bottom = { .x_coor = 20, .y_coor = 55 };
	struct display_point center_top = { .x_coor = 80, .y_coor = 55 };
	struct display_point bg1 = { .x_coor = 20, .y_coor = 53 };
	struct display_point bg2 = { .x_coor = 81, .y_coor = 57 };

	if (!color_initialized) {
		thermo_side = 0xFFFF;
		minColor = 0x04DF;
		actColor = 0xFFFF;
		maxColor = 0xF801;
		color_initialized = true;
	}

	int color = thermo_side;
	bool isHorizontal = false;

	int space = 0;
	struct display_point begin_ptn;
	struct display_point stop_ptn;
	struct display_point minus20degree;
	struct display_point minus201;
	struct display_point minus202;
	struct display_point minus203;
	struct display_point zerodegree;
	struct display_point zero1;
	struct display_point plus20degree;
	struct display_point plus201;
	struct display_point plus202;
	struct display_point plus40degree;
	struct display_point plus401;
	struct display_point plus402;

	if (center_bottom.x_coor == center_top.x_coor) {

		isHorizontal = false;
		space = (center_top.y_coor - center_bottom.y_coor) / 5;
		begin_ptn.x_coor = center_bottom.x_coor - ray;
		begin_ptn.y_coor = center_bottom.y_coor;

		stop_ptn.x_coor = center_top.x_coor + ray;
		stop_ptn.y_coor = center_top.y_coor;

		minus20degree.x_coor = center_bottom.x_coor;
		zerodegree.x_coor = center_bottom.x_coor;
		plus20degree.x_coor = center_bottom.x_coor;
		plus40degree.x_coor = center_bottom.x_coor;

		minus20degree.y_coor = center_top.y_coor - (space / 2) - (3 * space);
		zerodegree.y_coor = center_top.y_coor - (space / 2) - (2 * space);
		plus20degree.y_coor = center_top.y_coor - (space / 2) - (1 * space);
		plus40degree.y_coor = center_top.y_coor - (space / 2);
	}

	if (center_bottom.y_coor == center_top.y_coor) {
		isHorizontal = true;
		space = (center_top.x_coor - center_bottom.x_coor) / 5;
		begin_ptn.x_coor = center_bottom.x_coor;
		begin_ptn.y_coor = center_bottom.y_coor - ray;
		stop_ptn.x_coor = center_top.x_coor;
		stop_ptn.y_coor = center_top.y_coor + ray;

		minus20degree.y_coor = center_bottom.y_coor;
		zerodegree.y_coor = center_bottom.y_coor;
		plus20degree.y_coor = center_bottom.y_coor;
		plus40degree.y_coor = center_bottom.y_coor;

		minus20degree.x_coor = center_top.x_coor - (space / 2) - (3 * space);
		zerodegree.x_coor = center_top.x_coor - (space / 2) - (2 * space);
		plus20degree.x_coor = center_top.x_coor - (space / 2) - (1 * space);
		plus40degree.x_coor = center_top.x_coor - (space / 2);
	}

	if (isHorizontal) {
		minus203.x_coor = minus20degree.x_coor + 4;
		minus203.y_coor = minus20degree.y_coor + 20;

		minus202 = minus203;
		minus202.y_coor += 8;

		minus201 = minus202;
		minus201.y_coor += 8;

		zero1.x_coor = zerodegree.x_coor + 4;
		zero1.y_coor = zerodegree.y_coor + 20;

		plus202.x_coor = plus20degree.x_coor + 4;
		plus202.y_coor = plus20degree.y_coor + 20;

		plus201 = plus202;
		plus201.y_coor += 8;

		plus402.x_coor = plus40degree.x_coor + 4;
		plus402.y_coor = plus40degree.y_coor + 20;

		plus401 = plus402;
		plus401.y_coor += 8;

	} else {
		minus203.x_coor = minus20degree.x_coor - 20;
		minus203.y_coor = minus20degree.y_coor + 4;

		minus202 = minus203;
		minus202.x_coor -= 8;

		minus201 = minus202;
		minus201.x_coor -= 8;

		zero1.x_coor = zerodegree.x_coor - 20;
		zero1.y_coor = zerodegree.y_coor + 4;

		plus202.x_coor = plus20degree.x_coor - 20;
		plus202.y_coor = plus20degree.y_coor + 4;

		plus201 = plus202;
		plus201.x_coor -= 8;

		plus402.x_coor = plus40degree.x_coor - 20;
		plus402.y_coor = plus40degree.y_coor + 4;

		plus401 = plus402;
		plus401.x_coor -= 8;
	}

	struct display_circle circle1;
	circle1.x_coor = 40;
	circle1.y_coor = 20;
	circle1.radius = ray * 2;
	circle1.color = 0xffff;

	struct display_circle circle2;
	circle2.x_coor = 40;
	circle2.y_coor = 80;
	circle2.radius = ray;
	circle2.color = 0xffff;

	struct display_circle circle3;
	circle3.x_coor = 40;
	circle3.y_coor = 20;
	circle3.radius = ray * 1.5;
	circle3.color = 0x04DF;

	display_rect(bg1, bg2, 0x0000);
	display_rect(begin_ptn, stop_ptn, color);
	display_circle(circle1);
	display_circle(circle2);
	display_circle(circle3);

	display_line(minus20degree, 10, isHorizontal, color);
	display_caract(minus201, '-', color, isHorizontal);
	display_caract(minus202, '2', color, isHorizontal);
	display_caract(minus203, '0', color, isHorizontal);
	display_line(zerodegree, 10, isHorizontal, color);
	display_caract(zero1, '0', color, isHorizontal);
	display_line(plus20degree, 10, isHorizontal, color);
	display_caract(plus201, '2', color, isHorizontal);
	display_caract(plus202, '0', color, isHorizontal);
	display_line(plus40degree, 10, isHorizontal, color);
	display_caract(plus401, '4', color, isHorizontal);
	display_caract(plus402, '0', color, isHorizontal);
	scale = plus40degree.x_coor - minus20degree.x_coor;
}


extern void display_thermo_info(int temp) {
	if (!color_initialized) {
		thermo_side = 0xFFFF;
		minColor = 0x04DF;
		actColor = 0xFFFF;
		maxColor = 0xF801;
		color_initialized = true;
	}

	if (!thermo_initialized) {
		int initialValue = thermo_read();
		minValue = initialValue;
		maxValue = initialValue;
		thermo_initialized = true;
	}

	if (temp < -20) {
		temp = -20;
	}

	if (temp < minValue) {
		minValue = temp;
	}

	if (temp > maxValue) {
		maxValue = temp;
	}

	struct display_point mintemp1 = { .x_coor = 40, .y_coor = 44 };
	struct display_point mintemp2 = { .x_coor = 40, .y_coor = 36 };
	struct display_point mintemp3 = { .x_coor = 40, .y_coor = 28 };
	struct display_point mintemp4 = { .x_coor = 40, .y_coor = 20 };
	struct display_point mintemp5 = { .x_coor = 40, .y_coor = 12 };

	if (minValue < 0) {
		int minDisplayValue = -(minValue);
		if (minDisplayValue < -20) {
			minDisplayValue = -20;
		}
		display_caract(mintemp1, 'm', minColor, true);
		display_caract(mintemp2, '=', minColor, true);
		display_caract(mintemp3, '-', minColor, true);
		display_caract(mintemp4, '0' + (uint8_t) (minDisplayValue / 10),
				minColor, true);
		display_caract(mintemp5, '0' + (uint8_t) (minDisplayValue % 10),
				minColor, true);
	} else {
		display_caract(mintemp1, 'm', minColor, true);
		display_caract(mintemp2, '=', minColor, true);
		display_caract(mintemp3, ' ', minColor, true);
		display_caract(mintemp4, '0' + (uint8_t) (minValue / 10), minColor,
				true);
		display_caract(mintemp5, '0' + (uint8_t) (minValue % 10), minColor,
				true);
	}

	struct display_point ctemp1 = { .x_coor = 55, .y_coor = 44 };
	struct display_point ctemp2 = { .x_coor = 55, .y_coor = 36 };
	struct display_point ctemp3 = { .x_coor = 55, .y_coor = 28 };
	struct display_point ctemp4 = { .x_coor = 55, .y_coor = 20 };
	struct display_point ctemp5 = { .x_coor = 55, .y_coor = 12 };

	if (temp < 0) {
		int negTemp = -(temp);
		display_caract(ctemp1, 'C', actColor, true);
		display_caract(ctemp2, '=', actColor, true);
		display_caract(ctemp3, '-', actColor, true);
		display_caract(ctemp4, '0' + (uint8_t) (negTemp / 10), actColor, true);
		display_caract(ctemp5, '0' + (uint8_t) (negTemp % 10), actColor, true);
	} else {
		display_caract(ctemp1, 'C', actColor, true);
		display_caract(ctemp2, '=', actColor, true);
		display_caract(ctemp3, ' ', actColor, true);
		display_caract(ctemp4, '0' + (uint8_t) (temp / 10), actColor, true);
		display_caract(ctemp5, '0' + (uint8_t) (temp % 10), actColor, true);
	}

	struct display_point maxtemp1 = { .x_coor = 70, .y_coor = 44 };
	display_caract(maxtemp1, 'M', maxColor, true);
	struct display_point maxtemp2 = { .x_coor = 70, .y_coor = 36 };
	display_caract(maxtemp2, '=', maxColor, true);
	struct display_point maxtemp3 = { .x_coor = 70, .y_coor = 28 };
	display_caract(maxtemp3, ' ', maxColor, true);
	struct display_point maxtemp4 = { .x_coor = 70, .y_coor = 20 };
	display_caract(maxtemp4, '0' + (uint8_t) (maxValue / 10), maxColor, true);
	struct display_point maxtemp5 = { .x_coor = 70, .y_coor = 12 };
	display_caract(maxtemp5, '0' + (uint8_t) (maxValue % 10), maxColor, true);

	struct display_point blueRect1 = { .x_coor = 20, .y_coor = 53 };
	struct display_point blueRect2 = { .x_coor = 38, .y_coor = 57 };
	struct display_point minrect1 = { .x_coor = 38, .y_coor = 53 };
	struct display_point minrect2 = { .x_coor = 38
			+ ((20 + minValue) * scale) / 60, .y_coor = 57 };
	struct display_point actrect1 = { .x_coor = minrect2.x_coor, .y_coor = 53 };
	struct display_point actrect2 = { .x_coor = 38 + ((temp + 20) * scale) / 60,
			.y_coor = 57 };
	struct display_point maxrect1 = { .x_coor = actrect2.x_coor, .y_coor = 53 };
	struct display_point maxrect2 = { .x_coor = 38
			+ ((20 + maxValue) * scale) / 60, .y_coor = 57 };

	display_rect(blueRect1, blueRect2, 0x04DF);
	display_rect(maxrect1, maxrect2, maxColor);
	display_rect(actrect1, actrect2, actColor);
	display_rect(minrect1, minrect2, minColor);
}

extern int thermo_info_init(){
	thermo_side = 0xFFFF;
	minColor = 0x04DF;
	actColor = 0xFFFF;
	maxColor = 0xF801;
	return 0;
}

extern int thermo_change_color(int argc, char* argv[]){
	thermo_side = (int)argv[1];
	minColor = (int)argv[2];
	actColor = (int)argv[3];
	maxColor = (int)argv[4];
	return 0;
}


extern void display_caract(struct display_point position, uint8_t caract, uint32_t color, bool isHorizontal) {
	char test = 0;
	if (isHorizontal) {
		for (int i = 0; i < 8; i++) {
			oled_memory_size(position.x_coor-i, position.x_coor-i,position.y_coor-8, position.y_coor);
			test = fontdata_8x8[caract][i];
			test = ((test * 0x0802LU & 0x22110LU) | (test * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16;

			for (int j = 0; j < 8; j++) {
				if (test >= 128) {
					oled_color(color);
				} else {
					oled_color(0);
				}
				test = test << 1;
			}
		}
	} else {
		for (int i = 0; i < 8; i++) {
			oled_memory_size(position.x_coor, position.x_coor + 8,
					position.y_coor - i, position.y_coor - i);
			test = fontdata_8x8[caract][i];
			test = ((test * 0x0802LU & 0x22110LU) | (test * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16;
			for (int j = 0; j < 8; j++) {
				if (test >= 128) {
					oled_color(color);
				} else {
					oled_color(0);
				}
				test = test << 1;
			}
		}
	}
}

