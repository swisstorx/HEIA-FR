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
 * Project:		HEIA-FR / Embedded Systems
 *
 *
 * Author: 		Marc Roten / Sven Rouvinez
 * Date: 		3 Dec 2018
 */
#pragma once
#ifndef BUTTONS_H_
#define BUTTONS_H_

/*
* états possibles
*/
enum buttons_etats{
    open,
    closed,
    pressed,
    released
};

enum buttons_set{
    BUTTON_1,
    BUTTON_2,
    BUTTON_3,  
}
void buttons_init();


//return if button pressed
//to get 1 button, for example s3: (1<<17) & get_states_buttons
//uint32_t get_states_buttons();

extern enum buttons_etats buttons_get_state(enum buttons_set bouton);


#endif /* BUTTONS_H_ */
