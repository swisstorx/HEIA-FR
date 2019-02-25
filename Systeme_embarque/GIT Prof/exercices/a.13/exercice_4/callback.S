/* Interfacing C with assembleur
 * Exercice 4 : solution
 */

    .global callback_init, callback_attach, callback_detach, callback_call

/* Constant definition */
MAX_ELE	= 100

/* Uninitialized variables declation */
            .bss
/*
   struct Map {int key, CALLBACK_Function function; } map[100]; 
*/
map:        .space 8*MAX_ELE
map_top:

/* Implementation of assembler functions and methods */
            .text

/**
 * Method to initialize the callback library. 
 * 
 * extern void callback_init ();
 */
callback_init:
	nop
        ldr     r0, =map
        ldr     r1, =map_top
        sub     r1, r0
        mov     r1, r1, lsr #2
        mov	r2, #0
fill:   str	r2,[r0],#4
	subs	r1, #1
	bne	fill
        bx 	lr


/**
 * Method to attach a function to the library.
 *
 * extern int callback_attach (int key, CALLBACK_Function fnct, void* param);
 * r0 = key  --> r0 = status
 * r1 = fnct
 * r2 = param
 */
callback_attach:
	push	{r4}		@prolog: save used registers

	/* test if key is out of range: key >= MAX_ELE */
	ldr	r4, =MAX_ELE
	cmp	r0, r4
	movhs	r0, #-1		@return error, status = -1
	bhs	reta

	/* test if a function has already be attached to the specified key */
	ldr	r3, =map
	ldr	r4, [r3, r0, LSL #3]!
	cmp	r4, #0
	movne	r0, #-1		@return error, status = -1
	bne	reta

	/* all tests successfully passed, store function and param in the map */
	str	r1, [r3, #0]	@store function
	str	r2, [r3, #4]	@store param
	mov	r0, #0		@return success, status = 0

reta:	pop	{r4}		@epilog: restore used registers and return
        bx 	lr


/**
 * Method to detach a function from the library
 *
 * extern void callback_detach (int key);
 * r0 = key
 */
callback_detach:
	/* test if key is out of range: key >= MAX_ELE */
	ldr	r1, =MAX_ELE
	cmp	r0, r1
	bhs	retb

	/* test if a function has already be attached to the specified key */
	ldr	r1, =map
	ldr	r2, =0
	str	r2, [r1, r0, LSL #3]!	@clear fnct
	str	r2, [r1, #4]		@clear param

retb:	bx	lr



/**
 * Method to call an attached function based on its key
 *
 * extern int callback_call (int key, int arg1, int arg2, void* arg3);
 * r0 = key   --> r0 = status
 * r1 = arg1
 * r2 = arg2
 * r3 = arg3
 */
callback_call:
	push	{r4, r5, lr}	@prolog: save used registers

	/* test if key is out of range: key >= MAX_ELE */
	ldr	r4, =MAX_ELE
	cmp	r0, r4
	movhs	r0, #-1
	bhs	retc

	/* test if a function has already be attached to the specified key */
	ldr	r4, =map
	ldr	r5, [r4, r0, lsl #3]!
	cmp	r5, #0
	moveq	r0, #-1		@return error, status = -1
	beq	retc

	/* a function is attached to the key, then load the param and call 
	 * the function
	 *   prototype: int fnct (void* param, int arg1, int arg2, void* arg3);
	 *   r0 = param --> to load from map
	 *   r1 = arg1   --> already in
	 *   r2 = arg2   --> already in
	 *   r3 = arg3   --> already in
	 *   r5 = fnct to call
	 */
	ldr	r0, [r4, #4]	@load the param
	blx	r5		@call the function

retc:	pop	{r4, r5, pc}	@epilog: restore used registers and return




