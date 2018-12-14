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
 * Project:	HEIA-FR / Embedded Systems 2 Laboratory
 *
 * Abstract: Thermo
 *
 * Purpose:
 *
 * Origin:
 *
 * Author: 	Sven Rouvinez / Marc Roten
 * Date: 	09.12.2018
 *  */

#ifndef THERMO_H_
#define THERMO_H_

/*
 * Init the thermo
 */
void thermo_init();

/*
 * Return the current temperature
 */
int thermo_read();

#endif /* THERMO_H_ */
