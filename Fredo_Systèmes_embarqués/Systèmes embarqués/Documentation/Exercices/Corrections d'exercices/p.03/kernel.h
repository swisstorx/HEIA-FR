#pragma once
#ifndef KERNEL_H
#define KERNEL_H
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
 * Date:		19.03.2018
 */

#include <stdint.h>
#include <stdbool.h>

// definition of the possible states of a thread
enum kernel_states {
	KERNEL_TERMINATED, 
	KERNEL_RUNNING, 
	KERNEL_READY, 
	KERNEL_BLOCKED, 
};

// thread context
struct kernel_context {
	uint32_t regs[15];
	uint32_t psr;
};

// definition of the task control block (tcb)
struct kernel_tcb {
	struct kernel_context context;
	enum kernel_states state;

	struct kernel_tcb* t_next;	// used to chain all tcb
	struct kernel_tcb* s_next;	// used to chain blocked threads within a sema

	int32_t id;					// unique thread identification
	char name[32];				// thread name

	uint32_t stack_size;		// thread stack size in bytes
	uint32_t stack[];			// stack
};


extern void kernel_init();
extern void kernel_launch();
extern void kernel_yield();
extern void kernel_exit();

extern int32_t kernel_id();
extern const char* kernel_name();
extern struct kernel_tcb* kernel_running_task();
extern struct kernel_tcb* kernel_idle_task();

extern void kernel_add_tcb(struct kernel_tcb* tcb);
extern struct kernel_tcb* kernel_new_tcb(uint32_t stack_sz, const char* name);
extern int32_t kernel_new_taskid();

extern void kernel_interrupt_enable(int flags);
extern int kernel_interrupt_disable();

#endif
