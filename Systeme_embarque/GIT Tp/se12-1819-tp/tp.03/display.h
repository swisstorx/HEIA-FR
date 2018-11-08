<<<<<<< HEAD
/*
 * display.h
 *
 *  Created on: Nov 5, 2018
 *      Author: lmi
 */
#pragma once
#ifndef DISPLAY_H_
#define DISPLAY_H_

extern void display_init();
extern void display_clear();
void display_rectangle();
void display_swissFlag();
void display_circle(uint32_t x0, uint32_t y0, uint32_t r, uint32_t color);

#endif /* DISPLAY_H_ */
=======
#pragma once
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
 * Author: 		Marc Roten / Sven Rouvinez
 * Date: 		Nov 5, 2018
 */



#ifndef DISPLAY_H_
#define DISPLAY_H_




/*
 * Initialize display and LED
 */
void display_init();

/*
 * Set LED black to initialize
 */
void  display_clear();

/*
 * Draw a circle
 * @param x0 where on x to draw
 * @param y0 where on y to draw
 * @param r define the radius of circle
 * @param color color of circle in hexa
 */
void display_circle(uint32_t x0, uint32_t y0, uint32_t r, uint32_t color);

void display_bar(uint32_t x0, uint32_t y0, uint32_t r, uint32_t color);

void display_rectangle(uint32_t x1, uint32_t x2, uint32_t y1, uint32_t y2,uint32_t color);

#endif
>>>>>>> 48e57dca9bc9d3a42e0766d1d0aacaa2665bddf9
