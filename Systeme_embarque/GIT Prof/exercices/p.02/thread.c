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
 * Purpose:		Micro kernel service definition
 *
 * Author:		Daniel Gachet / HEIA-FR
 * Date:		21.03.2019
 */

#include <string.h>
#include <stdbool.h>
#include <am335x_dmtimer1.h>

#include "kernel.h"
#include "thread.h"

static struct kernel_tcb* delayed_threads;

// --- implementation of local services / methods -----------------------------

static void process_delayed_threads(void* param)
{
	(void)param;
	while (1) {
		uint64_t uptime = am335x_dmtimer1_get_uptime();
		struct kernel_tcb*  n = delayed_threads;
		struct kernel_tcb** i = &delayed_threads;
		while (n != 0) {
			if (n->delay <= uptime) {
				n->delay = 0;
				n->state = KERNEL_READY;
				*i = n->d_next;
				
			} else {
				i=&(n->d_next);
			}
			n = n->d_next;
		}
		thread_yield();
	}
}

// --- implementation of local services / methods -----------------------------

static void thread_startup (void* param, thread_t thread)
{
	thread (param);
	thread_exit();
}
 
// --- implementation of public services / methods ----------------------------

void thread_exit() 
{
	kernel_running_task()->state = KERNEL_TERMINATED;
 	thread_yield();
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


int thread_create(thread_t thread,void* param,
const char* name,uint32_t stack_size){
struct kernel_tcb* tcb = new_tcb(stack_size, name);
if (tcb == 0) return -1;
tcb->context.psr = 0x13; // mode
tcb->state = KERNEL_READY;
kernel_add_tcb(tcb);
return tcb->id;}

void thread_delay(uint32_t ms)
{
	struct kernel_tcb* th = kernel_running_task();
	th->delay = am335x_dmtimer1_get_uptime() + 
				((am335x_dmtimer1_get_frequency() / 1000) * ms);
	th->state = KERNEL_DELAYED;
	th->d_next = delayed_threads;
	delayed_threads = th;

	kernel_yield();
}

// ----------------------------------------------------------------------------
// --- micro kernel thread library initialization ------------------------------
// ----------------------------------------------------------------------------

void thread_init() 
{
	thread_create(process_delayed_threads, 0, "delayed_threads", 0);
}
