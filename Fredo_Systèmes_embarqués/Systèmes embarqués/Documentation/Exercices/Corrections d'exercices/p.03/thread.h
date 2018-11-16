#pragma once
#ifndef THREAD_H
#define TRHEAD_H
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

#include <stdint.h>

typedef void (*thread_t) (void* param);

extern void thread_init();

extern int  thread_create (
	thread_t thread, 
	void* param, 
	const char* name, 
	uint32_t stack_size);

extern void thread_exit();

extern void thread_yield();

extern const char* thread_name();

extern int thread_id();

#endif
