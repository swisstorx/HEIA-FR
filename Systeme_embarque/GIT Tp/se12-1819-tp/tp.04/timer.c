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

#include <am335x_clock.h>

// DMTimer TIOCP_CFG register bit definition
#define TIOCP_CFG_SOFTRESET 	(1<<1)

// DMTimer TISTAT register bit definition
#define TISTAT_RESETDONE	(1<<0)

// DMTimer TCLR register bit definition
#define TCLR_ST			(1<<0)
#define TCLR_AR			(1<<1)



static const enum am335x_clock_enable_timer_module timer2clock[]={
	AM335X_CLOCK_TIMER2,
	AM335X_CLOCK_TIMER3,
	AM335X_CLOCK_TIMER4,
	AM335X_CLOCK_TIMER5,
	AM335X_CLOCK_TIMER6,
	AM335X_CLOCK_TIMER7,
}

struct registre{
	uint32_t TIDR;		//00
	uint32_t res1[3];	//04--0f
	uint32_t TIOCP_CFG;	//10
	uint32_t res2[3];	 //14--1F
	uint32_t IRQ_EOI;
	uint32_t IRQSTATUS_RAW;
	uint32_t IRQSTATUS;
	uint32_t IRQENABLE_SET;
	uint32_t IRQENABLE_CLR;
	uint32_t IRQWAKEEN;
	uint32_t TCLR;
	uint32_t TCRR;
	uint32_t TLDR;
	uint32_t TTGR;
	uint32_t TWPS;
	uint32_t TMAR;
	uint32_t TCAR1;
	uint32_t TSICR;
	uint32_t TCAR1;
	uint32_t TSICR;
	uint32_t TCAR2;
};

static volatile struct timer_ctrl* timer_ctrl[]={
	(volatile struct timer_ctrl*) 0x48040000,
	(volatile struct timer_ctrl*) 0x48042000,
	(volatile struct timer_ctrl*) 0x48044000,
	(volatile struct timer_ctrl*) 0x48046000,
	(volatile struct timer_ctrl*) 0x48048000,
	(volatile struct timer_ctrl*) 0x4804a000,

}



static volatile struct dmtimer* dmtimer[]={
		[TIMER_2] =(struct dmtimer*) 0x48040000,
		[TIMER_3] =(struct dmtimer*) 0x48042000,
		[TIMER_4] =(struct dmtimer*) 0x48044000,
		[TIMER_5] =(struct dmtimer*) 0x48046000,
		[TIMER_6] =(struct dmtimer*) 0x48048000,
		[TIMER_7] =(struct dmtimer*) 0x4804a000,
};

void timer_init(enum timer2clock timer){
	static bool is_initialized = false;
	if(is_initialized)return;
	am335x_clock_enable_timer_module (timer2clock[timer]);
	volatile struct timer_ctrl pointer = timer_ctrl[timer];
	ctrl->tiocp_cfg = TIOCP_CFG_SOFTRESET;
	
}
