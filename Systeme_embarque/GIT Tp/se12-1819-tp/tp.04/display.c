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
#define RED 	0xff000


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
	oled_init(OLED_V100);
	oled_memory_size(bottom_left.x_coor, top_right.x_coor, bottom_left.y_coor,
			top_right.y_coor);
	for (unsigned int y = bottom_left.y_coor; y <= top_right.y_coor; y++) {
		for (unsigned int x = bottom_left.x_coor; x <= top_right.x_coor; x++) {
			oled_color(color);
		}
	}
}


void display_circle(uint32_t x0, uint32_t y0, uint32_t r, uint32_t color) {
 	for (int i = -r; i <= (int) r; i++) {
 		int a = sqrt(r * r - i * i);
		oled_memory_size(y0 - a, y0 + a, SCREEN_WIDTH - 1 - (x0 + i),
 				SCREEN_HEIGHT - 1 - (y0 + i));
 		for (unsigned int j = 2 * a; j > 0; j--) {
 			oled_color(color);
 		}
 	}

 }


//Afficher une chaine de caractere à une position
void display_string( int x, int y,char* c, uint32_t colorText,uint32_t colorBackGround){
    int index = 0;
    while(c[index] != 0) {
        display_char(c[index], x, y, colorText, colorBackGround);
        x+=8;
        index++;
    }
}

//Afficher un caratere à une position
void display_char(int c, int x, int y, uint32_t colorText, uint32_t colorBackGround){
	//chaque caractère fait 8x8
	oled_memory_size(x, (x+7), y, (y+7));
	//unsigned const char* bitmap = fontdata_8x8[(int)c];
    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            if (fontdata_8x8[(int)c][i] & (1 << (7-j))) {
                oled_color(colorText);
            } else {
                oled_color(colorBackGround);
            }
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

