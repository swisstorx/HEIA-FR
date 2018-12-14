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
 */

#include <am335x_gpio.h>
#include "am335x_spi.h"
#include <am335x_i2c.h>

#define	THERMO		0x48
#define TEMP		0
#define CONFIG		1
#define T_LOW		2
#define T_HIGH		3

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "thermo.h"

void thermo_init() {
	am335x_i2c_init(AM335X_I2C2, 400000);
}

int thermo_read() {
	uint8_t data[2] = { 0x80, 0 };
	int status = am335x_i2c_read(AM335X_I2C2, THERMO, TEMP, data, 2);
	int temp = (status == 0) ? (int8_t) data[0] : -128;
	return temp;
}

