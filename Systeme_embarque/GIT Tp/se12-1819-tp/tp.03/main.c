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
 * Abstract: main
 *
 * Purpose:
 *
 * Origin:
 *
 * Author: 	Sven Rouvinez/ Marc Roten
 * Date: 	10.12.2018
 */
// initialization
#include <am335x_gpio.h>
#include "am335x_spi.h"
#include <am335x_i2c.h>
#include <stdio.h>
#include <stdbool.h>

#include "oled.h"
#include "thermo.h"
#include "display.h"
#include "cli.h"
#include "shell.h"

int main() {
	display_init();
	thermo_init();
	display_thermo_basic_form();
	shell_init();
	while (true) {
		int temp = thermo_read();
		display_thermo_info(temp);
		shell_probe();
	}
}
