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
#define     DISPLAY_BLACK    0x0000
#define     DISPLAY_BLUE     0x001f
#define     DISPLAY_GREEN    0x07e0
#define     DISPLAY_GREY     0xa534
#define     DISPLAY_RED      0xf800
#define     DISPLAY_YELLOW   0xf7a0
#define     DISPLAY_WHITE    0xffff


#define		TOWER_HEIGHT	10
#define 	NUMBER_OF_PEGS	3
#define 	DISK_HEIGHT    	2
#define 	DISK_SPACING   	0
#define 	PEG_WIDTH    	2
#define 	BASE_WIDTH 		28
#define 	BASE_HEIGHT 	2
#define 	BASE_COLOR 		(DISPLAY_WHITE)
#define 	PEG_HEIGHT    	36
#define  	PEG_BASE    	28
#define     PEG_COLOR 		(DISPLAY_WHITE)
#define 	PEG_DISTANCE 	32
#define 	DISK_HEIGHT 	2
#define 	DISK_SPACE 		1
#define 	DISK_DISTANCE 	(DISK_HEIGHT + DISK_SPACE)
#define 	MARG_X 			1
#define 	MARG_Y 			32


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
	push	{r4-r5, lr}
	mov		r4, r0
	bl		display_init
	mov		r5, #NUMBER_OF_PEGS-1
1:	mov		r0, r5
	bl		draw_peg

	subs	r5,	#1
	bge		1b
	mov		r5,	#TOWER_HEIGHT-1
2:	mov		r1, r5
	mov		r0, r4
	bl		push_disk

	subs 	r5, #1
	bge		2b
	mov		r0,	#0
	mov		r1, #0
	ldr		r2, =WELCOME_STR
	ldr	r3, =DISPLAY_WHITE
	bl display_text

	mov r0,#0
	mov r1, #2
	ldr r2, =HANOI_STR
	ldr r3, =DISPLAY_WHITE
	bl display_text

	mov r0, #0
	mov r1, #9
	ldr r2, =MERRY_STR
	ldr r3, =DISPLAY_WHITE
	bl	display_text

	mov r0, #0
	mov r1, #11
	ldr r2, =NEW_YEAR_STR
	ldr r3, =DISPLAY_WHITE
	bl display_text

	pop	{r4-r5,pc}


/*
void tower_of_hanoi_move(int from, int to, int by, int height){
    if (height > 0) {
        height--;
        tower_of_hanoi_move(from, by, to, height);
        move_disk(from, to, height);
        tower_of_hanoi_move(by, to, from, height);
    }
}
*/
	.global tower_of_hanoi_move
tower_of_hanoi_move:
	nop
	subs	r3,#1
	bxlt	lr

	push	{r4-r7, lr}
	mov		r4, r0
	mov		r5, r1
	mov		r6, r2
	mov		r7,	r3
	mov		r1, r6
	mov		r2, r5
	bl		tower_of_hanoi_move

	mov		r0, r4
	mov		r1, r5
	mov		r2, r7
	bl		move_disk

	mov		r0, r6
	mov		r1, r5
	mov		r2, r4
	mov		r3,	r7
	bl		tower_of_hanoi_move

	pop		{r4-r7, pc}




/*
void draw_peg(int peg){
    display_rect(MARG_X + peg * PEG_DISTANCE,
    		MARG_Y,
			BASE_WIDTH,
			BASE_HEIGHT,
			BASE_COLOR);
    display_rect(MARG_X + BASE_WIDTH/2 + peg*PEG_DISTANCE - PEG_WIDTH/2,
    		MARG_Y,
			PEG_WIDTH,
			PEG_HEIGHT,
			PEG_COLOR);
}
*/
	.global draw_peg
draw_peg:
	nop
	push {r4-r5,lr}
	sub sp, #4
	mov r4, #PEG_DISTANCE
	mul r4, r0, r4
	ldr r3, =BASE_COLOR
	str r3, [sp]
	add r0, r4, #MARG_X
	mov r1, #MARG_Y
	mov r2, #BASE_WIDTH
	mov r3, #BASE_HEIGHT
	bl display_rect

	ldr r3, =PEG_COLOR
	str r3, [sp]
	add r0, r4, #(MARG_X + (BASE_WIDTH/2) - (PEG_WIDTH/2))
	mov r1, #MARG_Y
	mov r2, #PEG_WIDTH
	mov r3, #PEG_HEIGHT
	bl display_rect

	add sp, #4
	pop {r4-r5,pc}


	/*
void push_disk(int peg, int disk){
    draw_disk(peg, height[peg]++, disk);
}
*/
	.global push_disk
push_disk:
	nop
	push	{r4, lr}
	ldr		r4, =height
	ldrb	r3, [r4,r0]
	add		r2, r3,	#1
	strb	r2, [r4,r0]
	mov		r2, r1
	mov		r1,r3
	bl		draw_disk

	pop		{r4, pc}



  .global clear_disk
clear_disk:
    nop
    push    {r4-r5, lr}
    sub     sp,#4

    mov     r3, #PEG_DISTANCE
    mul     r4, r0, r3
    mov     r3, #DISK_DISTANCE
    mul     r5,r1,r3
    ldr     r3, =DISPLAY_BLACK
    str     r3, [sp]

    add     r0, r4, #(MARG_X)
    add     r1, r5, #(MARG_Y + BASE_HEIGHT + DISK_SPACE)
    mov     r2, #BASE_WIDTH
    mov     r3, #DISK_HEIGHT
    bl      display_rect

    ldr     r3, =PEG_COLOR
    str     r3, [sp]
    add     r0, r4, #(MARG_X + (BASE_WIDTH/2)- (PEG_WIDTH/2))
    add     r1, r5, #(MARG_Y + BASE_HEIGHT + DISK_SPACE)
    mov     r2, #PEG_WIDTH
    mov     r3, #DISK_HEIGHT
    bl      display_rect

    add     sp, #4
    pop     {r4-r5, pc}


/*
void draw_disk(int peg, int height, int disk){
    display_rect(MARG_X + peg * PEG_DISTANCE + BASE_WIDTH/2 - PEG_WIDTH/2 - (disk+1),
    		MARG_Y + BASE_HEIGHT + DISK_SPACE + height*DISK_DISTANCE,
			PEG_WIDTH + 2*(disk+1),
			DISK_HEIGHT,
			disk_color[disk]);
}
*/
	.global draw_disk
draw_disk:
	nop
	push {lr}
	sub sp,#4
	ldr r3,=disk_color
	ldr r3, [r3,r2,lsl #2]
	str r3, [sp]
	mov r3, #PEG_DISTANCE
	mul r0, r0, r3
	sub r0,r2
	add r0, #(MARG_X+ (BASE_WIDTH/2) - (PEG_WIDTH/2)-1)
	mov r3, #DISK_DISTANCE
	mul r1, r1, r3
	add r1, #(MARG_Y + BASE_HEIGHT + DISK_SPACE)
	lsl r2, #1
	add r2, #(PEG_WIDTH+2)
	mov r3, #DISK_HEIGHT
	bl display_rect
	add sp, #4
	pop {pc}




/*
void move_disk(int from, int to, int disk){
    clear_disk(from, --height[from]);
    push_disk(to,disk);
}
*/
	.global move_disk
move_disk:
	nop
	push {r4,lr}
	mov r4, r0
	mov r0, r1
	mov r1, r2
	bl push_disk
	ldr r3,=height
	ldrb r1, [r3, r4]
	sub r1, #1
	strb r1, [r3,r4]
	mov r0, r4
	bl clear_disk
	pop {r4, pc}




/*
int tower_of_hanoi_disks(){
	return TOWER_HEIGHT;
}
*/
.global tower_of_hanoi_disks
tower_of_hanoi_disks:
	nop
	mov		r0,#TOWER_HEIGHT
	bx		lr

