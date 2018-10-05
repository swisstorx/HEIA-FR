#pragma once

/*
 * buttons.h
 *
 *  Created on: Oct 1, 2018
 *      Author: sven
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_



#endif /* BUTTONS_H_ */


//initialise les gpio
void buttons_init();


//retourne les valeurs de tous les boutons
//Pour avoir un bouton en particulier, par exemple s3: (1<<17) & get_states_buttons
uint32_t get_states_buttons();
