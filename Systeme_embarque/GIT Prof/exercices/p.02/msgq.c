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
 * Autĥor:		Daniel Gachet / HEIA-FR / Telecoms
 * Date:		23.03.2019
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "kernel.h"
#include "sema.h"
#include "msgq.h"

struct msgq {
	struct msgq* chain;

	semaid_t sema_in;

	unsigned size;
	unsigned nb;
	unsigned in;
	unsigned out;
	void* msg[];

};

static struct msgq* msgq_list=0;

msgqid_t msgq_create(unsigned size)
{
	struct msgq* msgq = calloc (1, sizeof(struct msgq) + sizeof(void*) * size);
	if (msgq == 0) {
		return 0;
	}

	msgq->size = size;
	msgq->sema_in  = sema_create(0);

	// add message queue to the list
	msgq->chain = msgq_list;
	msgq_list = msgq;

	return (msgqid_t)msgq;
}

int msgq_destroy(msgqid_t msgq_id)
{
	struct msgq* msgq = (struct msgq*)msgq_id;

	if (sema_destroy(msgq->sema_in) != 0) {
		return -1;
	}

	// remove message queue from the list
	struct msgq** indirect = &msgq_list;
	while ((*indirect) != msgq) {
		indirect = &(*indirect)->chain; 
	}
	*indirect = msgq->chain;

	free (msgq);
	return 0;
}

int msgq_post (msgqid_t msgq_id, void* msg)
{
	struct msgq* msgq = (struct msgq*)msgq_id;
	int retcode = -1;

	int flags = kernel_interrupt_disable();
	if (msgq->nb < msgq->size) {
		msgq->nb++;
		msgq->msg[msgq->in++] = msg;	
		if (msgq->in >= msgq->size) {
			msgq->in = 0;
		}
		retcode = 0;
		sema_signal(msgq->sema_in);
	}
	kernel_interrupt_enable(flags);

	return retcode;

}

void* msgq_fetch(msgqid_t msgq_id)
{
	struct msgq* msgq = (struct msgq*)msgq_id;

	sema_wait(msgq->sema_in);
	int flags = kernel_interrupt_disable();
	msgq->nb--;
	void* msg = msgq->msg[msgq->out++];	
	if (msgq->out >= msgq->size) {
		msgq->out = 0;
	}
	kernel_interrupt_enable(flags);

	return msg;
}

void msgq_init()
{
}

