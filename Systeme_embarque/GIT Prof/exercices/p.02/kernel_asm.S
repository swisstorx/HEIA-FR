/**
 * Copyright 2019 University of Applied Sciences Western Switzerland / Fribourg
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
 * Project:		HEIA-FR / Embedded Systems 2 
 *
 * Abstract: 	Introduction to Operating System
 *
 * Purpose:		Implementation of lowlevel services
 *
 * Author:		Daniel Gachet / HEIA-FR
 * Date:		21.03.2019
 */

	.text
/* void kernel_transfer(...);
 * r0 = context address of the former task
 * r1 = context address of the new task
 */
	.global kernel_transfer
kernel_transfer:
	nop
	stmia	r0, {r0-r12,sp,lr}
	mrs		r2, cpsr
	str		r2, [r0, #15*4]

	ldr		r2, [r1, #15*4]
	msr		cpsr, r2
	ldmia	r1, {r0-r12,sp,pc}


	.global kernel_interrupt_enable
kernel_interrupt_enable:
	nop
	and		r0, #0xc0
	eor		r0, #0xc0
	mrs		r1, cpsr
	bic		r1, r1, r0
	msr		cpsr_c, r1
	bx		lr


	.global	kernel_interrupt_disable
kernel_interrupt_disable:
	nop
	mrs		r0, cpsr
	orr		r1, r0, #0xc0
	msr		cpsr_c, r1
	bx		lr



