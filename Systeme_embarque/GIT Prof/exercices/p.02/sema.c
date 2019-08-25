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
 * Project:	HEIA-FR / Embedded Systems 2 
 *
 * Abstract: Introduction to Operating System
 *
 * Purpose:	Micro kernel service definition
 *
 * Author:	Daniel Gachet / HEIA-FR
 * Date:	21.03.2019
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "kernel.h"
#include "sema.h"

// ----------------------------------------------------------------------------
// --- semaphore service implementation ---------------------------------------
// ----------------------------------------------------------------------------

struct sema {
	int32_t count;
	struct kernel_tcb* s_next;
	struct sema* chain;
};

static struct sema* sema_list = 0;

// --- public services ---

semaid_t sema_create (int initial_value)
{
	struct sema * sema = calloc (1, sizeof(*sema));
	if (sema == 0) {
		return 0;
	}

	sema->count = initial_value;
	sema->s_next = 0;

	// add sema to list
	sema->chain = sema_list;
	sema_list = sema;

	return (semaid_t)sema;
}

int sema_destroy (semaid_t sema_id)
{
	struct sema* sema = (struct sema*)sema_id;

	// check if still some thread pending within the sema
	if (sema->s_next != 0) {
		return -1;
	}

	// remove sema from list
	struct sema** indirect = &sema_list;
	while ((*indirect) != sema) {
		indirect = &(*indirect)->chain;
	}
	*indirect = sema->chain;

	free (sema);

	return 0;
}


void sema_signal (semaid_t sema_id)
{
	struct sema* sema = (struct sema*)sema_id;
	
	int flags = kernel_interrupt_disable();
	sema->count++;
	if (sema->s_next != 0) {
		sema->s_next->state = KERNEL_READY;
		sema->s_next = sema->s_next->s_next;
	}
	kernel_interrupt_enable(flags);
}


void sema_wait (semaid_t sema_id)
{
	struct sema* sema = (struct sema*)sema_id;

	int flags = kernel_interrupt_disable();
	sema->count--;
	if (sema->count < 0) {
		if (sema->s_next == 0) {
			sema->s_next = kernel_running_task();
		} else {
			struct kernel_tcb* next = sema->s_next;
			while (next->s_next != 0) next = next->s_next;
			next->s_next = kernel_running_task();
		}
		kernel_running_task()->s_next = 0;
		kernel_running_task()->state = KERNEL_BLOCKED;
	}
	kernel_interrupt_enable(flags);
	kernel_yield();
}

int sema_count(semaid_t sema_id)
{
	struct sema* sema = (struct sema*)sema_id;
	return sema->count;
}


// ----------------------------------------------------------------------------
// --- micro kernel sema library initialization -------------------------------
// ----------------------------------------------------------------------------

void sema_init() 
{
}
