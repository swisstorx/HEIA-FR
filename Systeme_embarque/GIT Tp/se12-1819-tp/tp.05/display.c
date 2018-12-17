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
 * This module is based on the software library developped by Texas Instruments
 * Incorporated - http://www.ti.com/ for its AM335x starter kit.
 *
 * Project: HEIA-FR / Embedded Systems 1 Laboratory
 *
 * Abstract: OLED Utility Library
 *
 * Purpose: This module implements servioces to display figures and texts 
 *          on the OLED-C display.
 *
 * Author: 	Daniel Gachet
 * Date: 	29.11.2018
 */

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "oled.h"
#include "font_8x8.h"

#include "display.h"

#define SCREEN_WIDTH    96
#define SCREEN_HEIGHT   96
#define BLACK           0

static int rotation = 270;

/* 
 * rotation (see https://matthew-brett.github.io/teaching/rotation_2d.html)
 *    x2 = x1 * cos(ß) - y1 * sin(ß)
 *    y2 = x1 * sin(ß) + y1 * cos(ß)
 * 
 *  --> ß=0°   : x2 = x1  / y2 = y1
 *  --> ß=90°  : x2 = -y1 / y2 = x1
 *  --> ß=180° : x2 = -x1 / y2 = -y1
 *  --> ß=270° : x2 = y1  / y2 = -x1
 */
static void memory_size(uint32_t x1, uint32_t x2, uint32_t y1, uint32_t y2)
{
    switch (rotation){
    case 0:
        oled_memory_size(x1, x2, y1, y2);
        break;
    case 270:
        oled_memory_size(y1, y2, (SCREEN_HEIGHT-1)-x2, (SCREEN_HEIGHT-1)-x1);
        break;
    case 180:
        oled_memory_size(
            (SCREEN_WIDTH-1)-x2, (SCREEN_WIDTH-1)-x1, 
            (SCREEN_HEIGHT-1)-y2, (SCREEN_HEIGHT-1)-y1);
        break;
    case 90:
        oled_memory_size((SCREEN_WIDTH-1)-y2, (SCREEN_WIDTH-1)-y1, x1, x2);
        break;
    }
}

void display_init()
{
#ifndef OLED_VERSION
	oled_init(OLED_V101);
#else
	oled_init(OLED_VERSION);
#endif
	display_clear();
}

void display_clear() 
{
    memory_size(
        0, SCREEN_WIDTH - 1, 
        0, SCREEN_WIDTH - 1
    );
    for (unsigned int y = 0; y < SCREEN_HEIGHT; y++) {
        for (unsigned int x = 0; x < SCREEN_WIDTH; x++) {
            oled_color(BLACK);
        }
    }
}

void display_char(int col, int row, char c, int color) 
{
    struct pixel s[8*8] = {0};
    struct pixel c_pixel = {.hword = color >> 8, .lword=color & 0xff};
    unsigned const char* bitmap = fontdata_8x8[(int) c];
    for (unsigned y = 0; y < 8; y++) {
        for (unsigned x = 0; x < 8; x++) {
            if (bitmap[7 - y] & (1 << x)) {
                switch (rotation) {
                case   0: s[(7-x)   + y*8    ] = c_pixel; break;
                case  90: s[(7-x)*8 + (7-y)  ] = c_pixel; break;
                case 180: s[x       + (7-y)*8] = c_pixel; break;
                case 270: s[x*8     + y      ] = c_pixel; break;
                }
            }
        }
    }
    uint32_t x1 = col*8;
    uint32_t y1 = SCREEN_HEIGHT-row*8-7;
    memory_size(x1, x1+7, y1, y1+7);
    oled_send_image(s, 8*8);
}

void display_text(int col, int row, const char* txt, int color) 
{
    for (int i = 0; ((i < 12) && (txt[i] != 0)); i++) {
        display_char(col + i, row, txt[i], color);
    }
}

void display_rect(
    uint32_t x0, uint32_t y0, 
    uint32_t w, uint32_t h, 
    uint32_t color)
{
    memory_size(x0, x0+w-1, y0, y0+h-1);
    for (unsigned int x = 0; x < w; x++) {
        for (unsigned int y = 0; y < h; y++) {
            oled_color(color);
        }
    }
}

void display_circle(uint32_t x0, uint32_t y0, uint32_t r, uint32_t color)
{
    for (int i = -r; i<=(int)r; i++) {
        int a = sqrt(r*r - i*i);
        memory_size(x0-a, x0+a, y0-i, y0-i);
        for (unsigned int j = 2*a; j>0; j--) {
            oled_color(color);
        }
    }
}


void display_change_rotation(uint32_t rot)
{
    display_clear();
    rotation = 270-rot;
}
