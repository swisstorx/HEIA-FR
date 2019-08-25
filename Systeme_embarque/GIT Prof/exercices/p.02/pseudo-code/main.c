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
 * Purpose:	This module implements a very basic multithreaded application
 *
 * Author:	Daniel Gachet / HEIA-FR
 * Date:	23.03.2019
 */

#include <stdio.h>
#include "kernel.h"
#include "thread.h"
#include "sema.h"
#include "msgq.h"

struct sema {
	semaid_t sema5;
	semaid_t sema6;
};

static void fnct (void* param) 
{
	printf ("%2d - %-12s %3d\n", thread_id(), thread_name(), (int)param);
}

static void thread1 (void* param)
{
	while (1) {
		fnct (param);
		thread_yield();
	}
}		

static void thread2 (void* param)
{
	while (1) {
		fnct (param);
		thread_yield();
	}
}	
	
static void thread3 (void* param)
{
	fnct (param);
}	
		
static void thread4 (void* param)
{
	fnct (param);
	thread_exit();
}	

static void thread5 (void* param)
{
	struct sema* sema = (struct sema*)param;
	while(1) {
		fnct((void*)205);
		sema_wait (sema->sema5);
		sema_signal (sema->sema6);
	}
}

static void thread6 (void* param)
{
	struct sema* sema = (struct sema*)param;
	while(1) {
		fnct((void*)206);
		sema_wait (sema->sema6);
		sema_signal (sema->sema5);
	}
}

static void thread7(void* param)
{
	msgqid_t msgq_id = (msgqid_t)param;
	int p = 0;
	while(1) {
		int retcode = msgq_post(msgq_id, (void*)p);
		if (retcode != 0) {
			thread_yield();
		} else {
			fnct((void*)p);
			p++;
		}

	}
}
							
static void thread8(void* param)
{
	msgqid_t msgq_id = (msgqid_t)param;
	while(1) {
		void* p = msgq_fetch(msgq_id);
		fnct(p);
		thread_yield();
	}
}

static void thread9(void* param)
{
	(void)param;
	int i=0;
	while(1) {
		fnct((void*)i++);
		thread_delay(2000);
	}
}

int main ()
{
	kernel_init();
	thread_init();
	sema_init();

	thread_create (thread1, (void*)10, "thread1", 0);
	thread_create (thread2, (void*)20, "thread2", 0);
	thread_create (thread3, (void*)30, "thread3", 0);
	thread_create (thread4, (void*)40, "thread4", 0);
	for (int i = 0; i < 5; i++) {
		char name[32];
		sprintf (name, "thread1.%d", i);
		thread_create (thread1, (void*)i, name, 0);
	}

	struct sema sema;
	sema.sema5 = sema_create (0);
	sema.sema6 = sema_create (1);
	thread_create (thread5, &sema, "th_sema1", 0);
	thread_create (thread6, &sema, "th_sema2", 0);

	msgqid_t msgq = msgq_create(5);
	thread_create (thread7, (void*)msgq, "th_msgq1", 0);
	thread_create (thread8, (void*)msgq, "th_msgq2", 0);

	thread_create (thread9, 0, "th_delay", 0);

	kernel_launch();

	return 0;
}
