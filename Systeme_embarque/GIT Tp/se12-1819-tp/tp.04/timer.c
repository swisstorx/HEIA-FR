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
 * Project:		HEIA-FR / Embedded Systems 4 Laboratory
 *
 *
 * Author: 		Marc Roten / Sven Rouvinez
 * Date: 		Dec 3, 2018
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <am335x_clock.h>
#include "timer.h"


// DMTimer TIOCP_CFG register bit definition
#define TIOCP_CFG_SOFTRESET 	(1<<0)

// DMTimer TISTAT register bit definition
#define TISTAT_RESETDONE	(1<<0)

// DMTimer TCLR register bit definition
#define TCLR_ST			(1<<0)
#define TCLR_AR			(1<<1)





struct timer_reg {
	uint32_t tidr;    //00
	uint32_t res1[3];  //04--0f
	uint32_t tiocp_cfg;  //10
	uint32_t res2[3];   //14--1F
	uint32_t irq_eoi;
	uint32_t irqstatus_raw;
	uint32_t irqstatus;
	uint32_t irqenable_set;
	uint32_t irqenable_clr;
	uint32_t irqwakeen;
	uint32_t tclr;
	uint32_t tcrr;
	uint32_t tldr;
	uint32_t ttgr;
	uint32_t twps;
	uint32_t tmar;
	uint32_t tcar1;
	uint32_t tsicr;
	uint32_t tcar2;
};

static volatile struct timer_reg* dmtimer[] = {
		(volatile struct timer_reg*) 0x48040000,
		(volatile struct timer_reg*) 0x48042000,
		(volatile struct timer_reg*) 0x48044000,
		(volatile struct timer_reg*) 0x48046000,
		(volatile struct timer_reg*) 0x48048000,
		(volatile struct timer_reg*) 0x4804A000 
};

static const enum am335x_clock_timer_modules timer2clock[] = {
		AM335X_CLOCK_TIMER2, AM335X_CLOCK_TIMER3, AM335X_CLOCK_TIMER4,
		AM335X_CLOCK_TIMER5, AM335X_CLOCK_TIMER6, AM335X_CLOCK_TIMER7
};


void dmtimer1_init(enum dmtimer_timers timer){
	am335x_clock_enable_timer_module(timer2clock[timer]);

	volatile struct timer_reg* ctrl = dmtimer[timer];
	ctrl->tiocp_cfg = TIOCP_CFG_SOFTRESET;
	while ((ctrl->tiocp_cfg & TIOCP_CFG_SOFTRESET) != 0)
		;

	ctrl->tldr = 0;
	ctrl->tcrr = 0;
	ctrl->ttgr = 0;
	ctrl->tclr = TCLR_AR | TCLR_ST;
}



 uint32_t dmtimer1_get_counter(enum dmtimer_timers timer){
		volatile struct timer_reg* ctrl = dmtimer[timer];
		return ctrl->tcrr;
 }
 uint32_t dmtimer1_get_frequency(){
	 return 24000000;
 }





































