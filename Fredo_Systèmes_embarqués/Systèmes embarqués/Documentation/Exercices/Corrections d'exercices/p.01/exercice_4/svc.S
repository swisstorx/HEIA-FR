/* Interrupt handling
 * Exercice 4 : solution
 */
	.data
	.align 8
usr_svc_handler: .long 0

        .text
	.align 8

// interrupt vector table  
vector_table_start:
1:	b	1b	// reset_handler
1:	b	1b	// undef_handler
	b	svc_handler
1:	b	1b	// prefetch_handler
1:	b	1b	// data_handler
1:	b	1b	// reserved_handler
1:	b	1b	// irq_handler
1:	b	1b	// fiq_handler

// low level svc handler
svc_handler:
	stmfd   sp!,{r1-r2, lr}
	ldr     r1,[lr, #-4]
	and     r1, #0x00ffffff
	ldr     r2,=usr_svc_handler
	ldr     r2,[r2]
	blx     r2
	ldmfd   sp!, {r1-r2, pc}^

// svc initialization method
	.global svc_init
svc_init:
	nop
	ldr     r3, =usr_svc_handler
	str     r0, [r3]

	// cp15 set vector base address 
	ldr	r1, =vector_table_start
	mcr	p15, #0, r1, c12, c0, #0

	// save lr to be able to come back after switching to user mode
	mov r0, lr

	// initialize the stack pointer registers
	msr     cpsr_c, #0xdf		// switch to system mode
	add     sp, r1, r2
	msr     cpsr_c, #0xd0		// switch to user mode

	bx	r0	// return to main program, but in user mode...

// svc_1 method
	.global svc_1_call
svc_1_call:
	nop
	svc	#1 
	bx	lr

// svc_1 method
	.global svc_5_call
svc_5_call:
	nop
	svc	#5 
	bx	lr

