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

#include <am335x_gpio.h>

#define GPIO1	    AM335X_GPIO1
#define S1			(15)
#define S2			(16)
#define S3		    (17)

// macro to compute number of elements of an array
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

static const struct gpio_init_in {
	uint32_t pin_nr;
} gpio_init_in[] = { { S1 }, { S2 }, { S3 } };

void buttons_init() {
	am335x_gpio_init(GPIO1);

	//set buttons in
	for (uint32_t i = 0; i < ARRAY_SIZE(gpio_init_in); ++i) {
		am335x_gpio_setup_pin_in(GPIO1, gpio_init_in[i].pin_nr,
				AM335X_GPIO_PULL_NONE, false);
		am335x_gpio_change_state(GPIO1, gpio_init_in[i].pin_nr, 1);
	}
}

uint32_t get_states_buttons() {

	return am335x_gpio_get_states(GPIO1);
}

