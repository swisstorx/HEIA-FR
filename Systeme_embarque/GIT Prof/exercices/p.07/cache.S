	.text

#define C1_CONTROL_ICACHE	(1<<12)	/* i-cache enable bit */
#define C1_CONTROL_DCACHE	(1<< 2)	/* d-cache enable bit */

// extern void cache_init();
	.global cache_init
cache_init:
	nop
	bx	lr


// extern void cache_i_enable();
	.global cache_i_enable
cache_i_enable:
	nop
	mrc	p15, 0, r0, c1, c0, 0
	orr	r0, #C1_CONTROL_ICACHE
	mcr	p15, 0, r0, c1, c0, 0
	bx	lr


// extern void cache_i_disable();
	.global cache_i_disable
cache_i_disable:
	nop
	mrc	p15, 0, r0, c1, c0, 0
	bic	r0, #C1_CONTROL_ICACHE
	mcr	p15, 0, r0, c1, c0, 0
	bx	lr

// extern void cache_d_enable();
	.global cache_d_enable
cache_d_enable:
	nop
	mrc	p15, 0, r0, c1, c0, 0
	orr	r0, #C1_CONTROL_DCACHE
	mcr	p15, 0, r0, c1, c0, 0
	bx	lr


// extern void cache_d_disable();
	.global cache_d_disable
cache_d_disable:
	nop
	mrc	p15, 0, r0, c1, c0, 0
	bic	r0, #C1_CONTROL_DCACHE
	mcr	p15, 0, r0, c1, c0, 0
	bx	lr

