#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H
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
 * Project: HEIA-FR / Embedded Systems 1 Laboratory
 *
 * Abstract: OLED Utility Library
 *
 * Purpose: This module implements servioces to display figures and texts 
 *          on the OLED-C display.
 *
 * Author: 	Daniel Gachet
 * Date: 	24.10.2018
 */

#include <stdint.h>

/**
 * some basic colors
 */
enum display_colors {
	DISPLAY_BLACK = 0x0000,
	DISPLAY_BLUE = 0x001f,
	DISPLAY_GREEN = 0x07e0,
	DISPLAY_GREY = 0xa534, //0xce79,
	DISPLAY_RED = 0xf800,
	DISPLAY_YELLOW = 0xf7a0,
	DISPLAY_WHITE = 0xffff,
};

/**
 * method to initialize the resources of the diplay module
 * this method should be called prior any other
 */
extern void display_init();

/**
 * method to clear the display (black)
 */
extern void display_clear();

/**
 * method to display an ascii char on the display in font 8x8
 * @param col column number (0..11), starting on top left
 * @param row rown number (0..11), starting on top
 * @param c character to display 
 * @param color display color in rgb565, background is black
 */
extern void display_char(int col, int row, char c, int color);

/**
 * method to display a string on the display in font 8x8
 * @param col column number (0..11), starting on top left
 * @param row rown number (0..11), starting on top
 * @param txt text to be displayed (max 12 characters) 
 * @param color display color in rgb565, background is black
 */
extern void display_text(int col, int row, const char* txt, int color);

/**
 * method to display a rectangle on the display
 * @param x0 x bottom left position of the rectagle, starting at bottom left
 * @param y0 y bottom left position of the rectagle, starting at bottom left
 * @param w width of the rectangle
 * @param h height of the rectangle
 * @param color display color in rgb565
 */
extern void display_rect(uint32_t x0, uint32_t y0, uint32_t w, uint32_t h,
		uint32_t color);

/**
 * method to display a circle on the display
 * @param x0 x center position of the circle, starting at bottom left
 * @param y0 y center position of the circle, starting at bottom left
 * @param r radius 
 * @param color display color in rgb565
 */
extern void display_circle(uint32_t x0, uint32_t y0, uint32_t r, uint32_t color);

/**
 * method to change the rotation of the display
 * @param rot rotation value (allowed: 0, 90, 180 and 270)
 */
extern void display_change_rotation(uint32_t rot);

#endif
