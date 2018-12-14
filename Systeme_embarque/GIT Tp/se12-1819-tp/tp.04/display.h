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
 * Project: HEIA-FR / Embedded Systems 1+2 Laboratory
 *
 * Abstract:  Declaration of dislpay.c
 *
 * Purpose:
 *
 * Author: Sven Rouvinez/ Marc Roten
 * Date:  5.11.18
 */


#ifndef DISPLAY_H_
#define DISPLAY_H_
#include <stdbool.h>

struct display_point {
	uint32_t x_coor;
	uint32_t y_coor;
};


struct display_caract {
 struct display_point pos;
 char caract;
 bool isUptodate;
};

/**
 * This method is used to initialize the display
 */
extern void display_init();

/**
 * With this method, you can clear all the pixels of the screen. You put all of them with the color black
 */
void display_clear();


extern void  display_clear();

//Afficher une chaine de caractere à une position
extern void display_string( int x, int y,char* c, uint32_t colorText,uint32_t colorBackGround);

//Afficher un caratere à une position
extern void display_char(int c, int x, int y, uint32_t colorText, uint32_t colorBackGround);




#endif
