#pragma once
#ifndef SEMA_H
#define SEMA_H
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

extern void sema_init();
extern int sema_create(int initial_value);
extern int sema_destroy(int sema_id);
extern int sema_wait(int sema_id);
extern int sema_signal(int sema_id);
extern int sema_count(int sema_id);

#endif
