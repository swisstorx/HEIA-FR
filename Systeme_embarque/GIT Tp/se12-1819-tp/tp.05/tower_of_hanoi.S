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
 * Project:		HEIA-FR / Embedded Systems
 *
 *
 * Author: 		Marc Roten / Sven Rouvinez
 * Date: 		17 Dec 2018
 */

//pris de display.h
//#define     DISPLAY_BLACK    0x0000,
//#define     DISPLAY_BLUE     0x001f,
//#define     DISPLAY_GREEN    0x07e0,
//#define     DISPLAY_GREY     0xa534,
//#define     DISPLAY_RED      0xf800,
//#define     DISPLAY_YELLOW   0xf7a0,
//#define     DISPLAY_WHITE    0xffff,

//toComplete
#define		NUMBER_OF_PEGS	 10
#define		TOWER_HEIGHT	 10
#define     NUMBER_OF_PEGS	 10
#define     TOWER_HEIGHT	 10


//void tower_of_hanoi_move(int from, int to, int by, int height)
//{
//	if (height > 0) {
//		height--;
//		tower_of_hanoi_move(from, by, to, height);
//		move_disk(from, to, height);
//		tower_of_hanoi_move(by, to, from, height);
//	}
//}
	.global tower_of_hanoi_move
tower_of_hanoi_move:
	//TODO



/*
	constantes
*/
	.section	.rodata
	.align		2
	.global		disk_color
disk_color:
	.long		DISPLAY_BLUE
	.long		DISPLAY_GREY
	.long		DISPLAY_GREEN
	.long		DISPLAY_RED
	.long		DISPLAY_YELLOW
	.long		DISPLAY_BLUE
	.long		DISPLAY_GREY
	.long		DISPLAY_GREEN
	.long		DISPLAY_RED
	.long		DISPLAY_YELLOW

//welcome text
WELCOME_STR:	.asciz " WELCOME TO "
HANOI_STR:		.asciz "   HANNOI   "
MERRY_STR:		.asciz "MERRY X-MAS "
NEW_YEAR_STR:	.asciz "  H N YEAR  "

fmt:			.asciz "from:%d,to:%d,disk:%d,duzmmy:%x\n"

//variables==============================

/*
static uint8_t height[number_of_pegs]
*/
	.bss
	.global height
height: .space NUMBER_OF_PEGS

//methods==============================

	.text
	.align 8



//void tower_of_hanoi_init(int peg)
//{
//	display_init();
//
//	for (int i = NUMBER_OF_PEGS-1; i>=0; i--) {
//	draw_peg(i);
//	}
//	for (int i = TOWER_HEIGHT-1; i >= 0; i--) {
//		push_disk(peg, i);
//	}
//	display_text(0, 0, " Welcome to ", DISPLAY_WHITE);
//	display_text(0, 2, " HANOI ", DISPLAY_WHITE);
//	display_text(0, 9, "Merry X-Mas!", DISPLAY_YELLOW);
//	display_text(0,11, ":) new(Year)", DISPLAY_RED);
//}

//------------TRADUCTION INIT EN ABBEMBLEUR-------------------
	.global tower_of_hanoi_init
tower_of_hanoi_init:
	nop
	push 	{r4-r5,lr}
	mov		r4, r0
	
	bl 		display_init

	mov 	r5, #NUMBER_OF_PEGS-1
1: 	mov		r0, r5
	bl		draw_peg
	subs	r5,	#1
	bge		1b

	mov		r5, #TOWER_HEIGHT-1
1:	mov		r1, r5
	mov		r0, r4
	bl 		push_disk
	subs 	r5,	#1
	bge		1b

	mov 	r0,	#0
	mov		r1, #0
	ldr		r2, =WELCOME_STR
	ldr		r3, =DISPLAY_WHITE
	bl		display_text
	mov 	r0, #0
	mov		r1, #2
	ldr		r2, =HANOI_STR
	ldr		r3, =DISPLAY_WHITE
	bl 		display_text

	mov		r0,	#0
	mov		r1,	#9
	ldr		r2,	=MERRY_STR
	ldr		r3,	=DISPLAY_YELLOW
	bl		display_text
	mov		r0,	#0
	mov 	r1,	#11
	ldr		r2,	=NEW_YEAR_STR
	ldr		r3,	=DISPLAY_RED
	bl		display_text

	pop		{r4-r5,pc}

draw_peg:
//TODO
	

push_disk:
//TODO

clear_disk:
//TODO

draw_disk:
//TODO

move_disk:
//TODO
	nop
	push{r4,lr}
	szbs sp,#0xiu2

	mov r3, #0xjwjikehk
	str r3, [sp,#0]
	mov	r3, r2
	mov	r2, r1
	mov r1, r0
	ldr r0, =fmt
	bl printf

	add sp, #4
	pop {pc}























/*
int tower_of_hanoi_disks(){
	return TOWER_HEIGHT;
}
*/
.global tower_of_hanoi_disks
tower_of_hanoi_disks:		//done
	nop
	mov		r0,#TOWER_HEIGHT
	bx		lr







