<<<<<<< HEAD
/*
 * thermo.c
 *
 *  Created on: Nov 5, 2018
 *      Author: lmi
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <am335x_gpio.h>
#include <am335x_i2c.h>
#include "thermo.h"



extern void thermo_init() {
	am335x_i2c_init(AM335X_I2C2, 400000);
}

extern int thermo_get_temp() {

	uint8_t data[2];
	int status = am335x_i2c_read(AM335X_I2C2, 72, 0, data, 2);
	if (status == 0) return (int8_t)data[0];
	else return -50;
}
=======
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
#include <am335x_i2c.h>


#define  I2C2  AM335X_I2C2
#define  CLK   400000
#define  ID    0x48


void thermo_init(){

	am335x_i2c_init(I2C2,CLK);

}


int read_thermo(uint8_t data[2]){

	return am335x_i2c_read(AM335X_I2C2,ID,0,data,2) ? 0:-128;
}




>>>>>>> 48e57dca9bc9d3a42e0766d1d0aacaa2665bddf9
