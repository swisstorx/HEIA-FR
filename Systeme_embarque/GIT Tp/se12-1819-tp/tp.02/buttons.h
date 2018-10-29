

/*
 * buttons.h
 *
 *  Created on: Oct 1, 2018
 *      Author: sven
 *      Modified: Marc
 */
#pragma once
#ifndef BUTTONS_H_
#define BUTTONS_H_



#endif /* BUTTONS_H_ */



void buttons_init();


//return if button pressed
//to get 1 button, for example s3: (1<<17) & get_states_buttons
uint32_t get_states_buttons();
