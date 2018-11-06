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
