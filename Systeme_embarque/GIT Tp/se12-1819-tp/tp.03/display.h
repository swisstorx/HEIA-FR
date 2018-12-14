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

#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H

struct display_point {
   uint32_t  x_coor;
   uint32_t y_coor;
};

struct display_circle {
   uint32_t x_coor;
   uint32_t y_coor;
   uint32_t radius;
   uint32_t color;
};


struct display_caract {
 struct display_point pos;
 char caract;
 bool isUptodate;
};

/**
 * initialize the display
 */
extern void display_init();

/**
 * Set all pixel to BLACK
 */
void display_clear();

/**
 *
 *Display rectangle
 */
extern void display_rect(struct display_point bottom_left, struct display_point top_right, uint32_t color);

/**
 * Display circle
 */
extern void display_circle(struct display_circle);

/**
 * Display basic thermo
 */
extern void display_thermo_basic_form();

/**
 * Write a caractere at a position set
 */
extern void display_caract(struct display_point position, uint8_t caract, uint32_t color, bool isHorizontal);

/**
 * Display a line
 */
extern void display_line(struct display_point start, int size, bool isHorizontal, uint32_t color);

/**
 * Reset values of the temp
 */
extern void display_thermo_info(int temp);

/**
 * Reset registered temperature
 */
extern int thermo_info_init();

extern int thermo_change_color(int argc, char* argv[]);

#endif
