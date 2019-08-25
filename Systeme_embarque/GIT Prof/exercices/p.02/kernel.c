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
 * Abstract:	Introduction to Operating System
 *	
 * Purpose:		Micro kernel service definition
 *
 * Author:		Daniel Gachet / HEIA-FR
 * Date:		21.03.2019
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "kernel.h"

extern void kernel_transfer(
	struct kernel_context* former, 
	struct kernel_context* new);

static struct kernel_tcb idle_task = { // kernel idle task
	.state = KERNEL_RUNNING,
	.t_next = &idle_task,
	.id = 0,
	.name = "idle",
	.stack_size = 0,
};

static struct kernel_tcb* running_task  = &idle_task;

// --- implementation of local services / methods -----------------------------

// this method shall be called only from the idle task
// @param head tcb of idle task 
static void process_terminated_tasks(struct kernel_tcb* head)
{
	struct kernel_tcb* prev = head;
	while(prev->t_next != head) {
		struct kernel_tcb* actual = prev->t_next;
		if (actual->state == KERNEL_TERMINATED) {
			prev->t_next = actual->t_next;
			free(actual);
		} else {
			prev = actual;
		}
	}
}

// this method shall be called to get a new task id
static int32_t kernel_new_taskid()
{
	static int32_t  task_id = 0; // should be 0, 0 is used for init/idle task
	task_id++;
	return task_id;
}

// --- implementation of public services / methods ----------------------------

struct kernel_tcb* kernel_new_tcb(uint32_t stack_sz, const char* name)
{
	struct kernel_tcb* tcb = malloc (sizeof(struct kernel_tcb) + stack_sz);
	if (tcb != 0) {
		memset (tcb, 0, sizeof(struct kernel_tcb));
		tcb->stack_size = stack_sz;
		tcb->id = kernel_new_taskid();
		strncpy (tcb->name, name, sizeof(tcb->name)-1);
	}
	return tcb;
}

void kernel_add_tcb(struct kernel_tcb* tcb)
{
	tcb->t_next = idle_task.t_next;
	idle_task.t_next = tcb;
}

struct kernel_tcb* kernel_running_task()
{
	return running_task;
}

void kernel_yield()
{
	struct kernel_tcb* former_task = running_task;
	struct kernel_tcb* new_task = former_task->t_next;

	if (former_task->state == KERNEL_RUNNING) former_task->state = KERNEL_READY;
	while (new_task->state != KERNEL_READY) new_task = new_task->t_next;

	running_task = new_task;
	new_task->state = KERNEL_RUNNING;

	kernel_transfer(&former_task->context, &new_task->context);
}

void kernel_launch()
{
	while(1) {
		kernel_interrupt_enable(0);
		kernel_yield();
		process_terminated_tasks(running_task);
	}
}

// --- micro kernel initialization --------------------------------------------
void kernel_init() 
{ }
