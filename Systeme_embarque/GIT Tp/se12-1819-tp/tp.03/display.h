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
