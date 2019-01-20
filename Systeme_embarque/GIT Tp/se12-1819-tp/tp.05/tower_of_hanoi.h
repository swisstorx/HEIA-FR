#pragma once
#ifndef TOWER_OF_HANOI
#define TOWER_OF_HANOI
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
 * Project:	HEIA-FR / Embedded Systems 1 Laboratory
 *
 * Abstract: Introduction the C programming language
 *
 * Purpose:	Game tower of hanoi.
 *
 * Author: 	Daniel Gachet
 * Date: 	25.11.2018
 */

/**
 * method to initialize the resources the the module and 
 * to draw the initial tower
 * @param peg start peg 
 */
extern void tower_of_hanoi_init(int peg);

/**
 * method the move the tower
 * @param from   origin peg
 * @param to     destination peg 
 * @param by     peg to use to move the tower
 * @param height number of disks to be moved
 */
extern void tower_of_hanoi_move(int from, int to, int by, int height);

/**
 * method to get the number of disks composing the tower
 * @return number of disks
 */
extern int tower_of_hanoi_disks();


/**
 *
 * method to draw a peg
 *
 * */
extern void draw_peg(int peg);


#endif
