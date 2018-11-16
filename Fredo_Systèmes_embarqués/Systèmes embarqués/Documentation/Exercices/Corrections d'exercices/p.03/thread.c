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
 * Project:		HEIA-FR / Embedded Systems 2 
 *
 * Abstract: 	Introduction to Operating System
 *
 * Purpose:		Micro kernel service definition
 *
 * Author:		Daniel Gachet / HEIA-FR
 * Date:		18.03.2018
 */

#include <string.h>
#include <stdbool.h>

#include "kernel.h"
#include "thread.h"

// --- implementation of local services / methods -----------------------------

static void thread_startup (void* param, thread_t thread)
{
	thread (param);
	thread_exit();
}
 
// --- implementation of public services / methods ----------------------------

void thread_exit() 
{
 	kernel_exit();
}

void thread_yield() 
{
	kernel_yield();
}

const char* thread_name()
{
	return kernel_running_task()->name;
}

int thread_id()
{
	return kernel_running_task()->id;
}


int thread_create(
	thread_t thread, 
	void* param, 
	const char* name, 
	uint32_t stack_size)
{
	stack_size = (stack_size < 0x4000) ? 0x4000 : (stack_size + 8);
	struct kernel_tcb* tcb = kernel_new_tcb(stack_size, name);
	if (tcb == 0) return -1;

	tcb->context.regs[0] = (uint32_t)param;
	tcb->context.regs[1] = (uint32_t)thread;
	tcb->context.regs[13] = (((uint32_t)&tcb->stack[stack_size/4])/8)*8;
	tcb->context.regs[14] = (uint32_t)thread_startup;
	tcb->context.psr = 0x13; // mode: supervisor; IRQ & FIQ enabled 
	tcb->state = KERNEL_READY;

	kernel_add_tcb(tcb);

	return tcb->id;
}

// ----------------------------------------------------------------------------
// --- micro kernel thread library initialization ------------------------------
// ----------------------------------------------------------------------------

void thread_init() 
{
}
