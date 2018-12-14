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

#include <stdbool.h>

/**
* method to initialize the resoures of the buttons
* this method shall be called prior any other.
*/
extern void button_init();


/**
* method to know if the button S1 is pressed
*/
extern bool button_s1_is_pressed();


/**
* method to know if the button S2 is pressed
*/
extern bool button_s2_is_pressed();


/**
* method to know if the button S3 is pressed
*/
extern bool button_s3_is_pressed();


#endif /* BUTTON_H */






