/* Interfacing C with assembleur
 * Exercice 3 : solution
 */

	.global	add, add_fp, add_c, main_asm

	.data
value1:	.word 10
value2:	.word 100

	.bss
result:	.space 4

	.text

/* stack without usage of a frame pointer
 *
 *         +--------+
 *     SP  |   r0   |
 *         +--------+
 *     +4  |   r1   |
 *         +--------+
 *     +8  | value1 |
 *         +--------+
 *    +12  | value2 |
 *         +--------+
 *    +16  | result |
 *         +--------+
 */
add:
	nop
	push	{r0-r1}
	ldr	r0, [sp, #8]	@load value1
	ldr	r1, [sp, #12]	@load value2
	add	r0, r0, r1
	ldr	r1, [sp, #16]	@load address of result
	str	r0, [r1]
	pop	{r0-r1}
	bx	lr


/* stack with usage of a frame pointer
 *
 *         +--------+
 * -12/SP  |   r0   |
 *         +--------+
 *     -8  |   r1   |
 *         +--------+
 *     -4  |   fp   | @ frame pointer / r11
 *         +--------+
 *  FP (0) |   lr   | @ return address
 *         +--------+
 *     +4  | value1 |
 *         +--------+
 *     +8  | value2 |
 *         +--------+
 *    +12  | result |
 *         +--------+
 */
add_fp:
	nop
	push	{r0-r1,fp,lr}
	add	fp, sp, #0xc	@offset to fp from sp (r0,r1,fp,lr)
	ldr	r0, [fp, #0x4]	@load value1
	ldr	r1, [fp, #0x8]	@load value2
	add	r0, r0, r1
	ldr	r1, [fp, #0xc]	@load address of result
	str	r0, [r1]
	pop	{r0-r1,fp,pc}

/* with ARM C conventions */
add_c:
	nop
	add	r0, r0, r1
	bx	lr


main_asm:
	nop
	/* call add without fp */
	sub	sp,#3*4
	ldr	r0,=value1
	ldr	r0,[r0]
	str	r0,[sp, #0]
	ldr	r0,=value2
	ldr	r0,[r0]
	str	r0,[sp, #4]
	ldr	r0,=result
	str	r0,[sp, #8]
	bl	add
	add	sp, #3*4

	/* call add with fp */
	sub	sp,#3*4
	ldr	r0,=value1
	ldr	r0,[r0]
	str	r0,[sp, #0]
	ldr	r0,=value2
	ldr	r0,[r0]
	str	r0,[sp, #4]
	ldr	r0,=result
	str	r0,[sp, #8]
	bl	add_fp
	add	sp, #3*4

	/* call a la C */
	ldr	r0,=value1
	ldr	r0,[r0]
	ldr	r1,=value2
	ldr	r1,[r1]
	bl	add_c
	ldr	r1,=result
	str	r0,[r1]

	bx	lr


