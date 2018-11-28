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
 * Project:		HEIA-FR / Embedded Systems TODO Laboratory
 *
 * Abstract:	TODO
 *
 * Author: 		Marc Roten / Sven Rouvinez
 * Date: 		Nov 5, 2018
 */

#include <am335x_i2c.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "oled.h"
#include "font_8x8.h"
#include "display.h"

#define SCREEN_WIDTH 96
#define SCREEN_HEIGHT 96
#define BLACK   0

void display_init() {
	oled_init(OLED_V100);
	display_clear();
}

void display_clear() {

	oled_memory_size(0, SCREEN_WIDTH - 1, 0, SCREEN_WIDTH - 1);

	for (unsigned int y = 0; y < SCREEN_HEIGHT; y++) {
		for (unsigned int x = 0; x < SCREEN_HEIGHT; x++) {
			oled_color(BLACK);
		}
	}
}

extern void display_rectangle(struct display_point bottom_left,
		struct display_point top_right, uint32_t color) {
	oled_init(100);
	oled_memory_size(bottom_left.x_coor, top_right.x_coor, bottom_left.y_coor,
			top_right.y_coor);
	for (unsigned int y = bottom_left.y_coor; y <= top_right.y_coor; y++) {
		for (unsigned int x = bottom_left.x_coor; x <= top_right.x_coor; x++) {
			oled_color(color);
		}
	}
}

// void display_rectangle(uint32_t x1, uint32_t x2, uint32_t y1, uint32_t y2,uint32_t color) {
// 	oled_memory_size(x1, x2, y1, y2);

// 	for (unsigned i = x1; i < x2; i++) {
// 		for (unsigned j = y1; j < y2; j++) {

// 			oled_color(color);
// 		}
// 	}
// }

// void display_circle(uint32_t x0, uint32_t y0, uint32_t r, uint32_t color) {
// 	for (int i = -r; i <= (int) r; i++) {
// 		int a = sqrt(r * r - i * i);

// 		oled_memory_size(y0 - a, y0 + a, SCREEN_WIDTH - 1 - (x0 + i),
// 				SCREEN_HEIGHT - 1 - (y0 + i));
// 		for (unsigned int j = 2 * a; j > 0; j--) {
// 			oled_color(color);
// 		}
// 	}

// }

extern void display_circle(struct display_point center, int32_t ray,
		uint32_t color) {
	int size = 0;
	//oled_init(100);
	for (int i = -(ray); i <= ray; i++) {
		size = sqrt((ray * ray) - (i * i));
		//oled_init(100);
		oled_memory_size(center.x_coor - size, center.x_coor + size,
				center.y_coor + i, center.y_coor + i);
		for (int r = 0; r <= (2 * size); r++) {
			oled_color(color);
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

extern void display_thermo_basic_form(struct display_point center_bottom,
		struct display_point center_top, int32_t ray, uint32_t color) {
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

	display_circle(center_bottom, ray * 2, color);
	display_circle(center_top, ray, color);
	display_rectangle(begin_ptn, stop_ptn, color);

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
}

extern void display_caract(struct display_point position, uint8_t caract,
		uint32_t color, bool isHorizontal) {
	char test = 0;
	if (isHorizontal) {
		for (int i = 0; i < 8; i++) {
			oled_memory_size(position.x_coor - i, position.x_coor - i,
					position.y_coor - 8, position.y_coor);
			test = fontdata_8x8[caract][i];

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

