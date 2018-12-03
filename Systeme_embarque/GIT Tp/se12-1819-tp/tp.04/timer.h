#pragma once
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
 * Author: 		Marc Roten / Sven Rouvinez
 * Date: 		Dec 3, 2018
 */
#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>

enum dmtimer_set{
	DMTIMER_2,
	DMTIMER_3,
	DMTIMER_4,
	DMTIMER_5,
	DMTIMER_6,
	DMTIMER_7,
};
/**
 * we init our timer to zero
 */
extern void dmtimer1_init();


/**
 * we get the value of our counter
 */
extern uint32_t dmtimer1_get_counter();


/**
 * get the frequency
 */
extern uint32_t dmtimer1_get_frequency();


#endif

