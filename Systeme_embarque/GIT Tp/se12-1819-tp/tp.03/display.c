/*
 * display.c
 *
 *  Created on: Nov 5, 2018
 *      Author: lmi
 */
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "oled.h"
#include "font_8x8.h"

#include "display.h"

#define SCREEN_WIDTH 	96
#define SCREEN_HEIGHT 	96
#define BLACK 	0
#define RED 	0xff000
#define WHITE 	0xffff

void display_init(){
	oled_init();
	display_clear();
}
void display_clear(){
	oled_init();
	oled_memory_size(0,SCREEN_WIDTH -1, 0, SCREEN_WIDTH -1);
	for(unsigned int y=0;y<SCREEN_HEIGHT;y++){
		for(unsigned int x=0;x<SCREEN_WIDTH;x++){
			oled_color(BLACK);
		}

	}
}

void display_swissFlag(){
	display_rectangle(0, 0,96 ,96,RED ); //x1,y1,x2,y2
	display_rectangle(38,16,57,79,WHITE ); //x1,y1,x2,y2
	display_rectangle(16,38,79,57,WHITE );
}

void display_rectangle(uint32_t x1,uint32_t y1, uint32_t x2,  uint32_t y2,uint32_t color){
	/*
	 * 	oled_memory_size(33,53 , 22,65 ); //x1,x2,y1,y2
		oled_color(0xffff);
	 */
	for(unsigned i=x1;i<x2;i++){
		for(unsigned j=y1;j<y2;j++){
			oled_memory_size(i,i,j,j);
			oled_color(color);
		}
	}
}

void display_circle(uint32_t x0, uint32_t y0, uint32_t r, uint32_t color){
    for(int i = -r; i<=(int)r; i++){
        int a = sqrt(r*r - i*i);

        oled_memory_size(y0-a, y0+a, SCREEN_WIDTH-1-(x0+i), SCREEN_HEIGHT-1-(y0+i));
        for(unsigned int j = 2*a; j>0;j--){
            oled_color(color);
        }
    }
}

