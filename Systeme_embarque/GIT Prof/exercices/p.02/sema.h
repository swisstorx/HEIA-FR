#pragma once
#ifndef SEMA_H
#define SEMA_H
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

typedef void* semaid_t;

extern void sema_init();
extern semaid_t sema_create(int initial_value);
extern int sema_destroy(semaid_t sema_id);
extern void sema_wait(semaid_t sema_id);
extern void sema_signal(semaid_t sema_id);
extern int sema_count(semaid_t sema_id);

#endif
