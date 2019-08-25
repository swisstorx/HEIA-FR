#pragma once
#ifndef MSGQ_H
#define MSGQ_H
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

typedef void* msgqid_t;

extern void msgq_init();
extern msgqid_t msgq_create (unsigned size);
extern int mgsq_destroy (msgqid_t msgq_id);
extern int msgq_post    (msgqid_t msgq_id, void* msg);
extern void* msgq_fetch (msgqid_t msgq_id);

#endif
