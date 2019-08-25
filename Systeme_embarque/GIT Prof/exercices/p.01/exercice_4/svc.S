/* Interrupt handling
 * Exercice 4 : solution
 */
    .text
	.align 5

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
	stmfd   sp!,{lr}
	ldr     r1,[lr, #-4]
	and     r1, #0x00ffffff
	bl		usr_svc_handler
	ldmfd   sp!, {pc}^

// svc initialization method
	.global svc_init
svc_init:
	nop

	// cp15 set vector base address 
	ldr	r2, =vector_table_start
	mcr	p15, #0, r2, c12, c0, #0

	// save lr to be able to come back after switching to user mode
	mov r2, lr

	// initialize the stack pointer registers
	msr     cpsr_c, #0xdf		// switch to system mode
	add     sp, r0, r1
	msr     cpsr_c, #0xd0		// switch to user mode

	bx	r2	// return to main program, but in user mode...

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

