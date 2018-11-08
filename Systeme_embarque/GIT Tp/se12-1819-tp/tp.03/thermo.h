<<<<<<< HEAD
/*
 * display.h
 *
 *  Created on: Nov 5, 2018
 *      Author: lmi
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

extern void thermo_init();
extern int thermo_get_temp();

#endif /* DISPLAY_H_ */
=======
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
 * Project:		HEIA-FR / Embedded Systems TODO Laboratory
 *
 * Abstract:	TODO
 *
 * Author: 		Marc Roten / Sven Rouvinez
 * Date: 		Nov 5, 2018
 */
#ifndef THERMO_H_
#define THERMO_H_

#endif
#include <stdio.h>

void thermo_init();

/*
 * read temparature from thermometer
 * @param data array of data, data[0] is the temperature
 *
 *
 * @return int status, 0=success, -1=error
 */
int read_thermo(uint8_t data[2]);
>>>>>>> 48e57dca9bc9d3a42e0766d1d0aacaa2665bddf9
