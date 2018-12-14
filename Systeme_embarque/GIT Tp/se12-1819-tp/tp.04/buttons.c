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



#include "buttons.h"
#include <am335x_gpio.h>

// pin definition for buttons access
#define BTN_GPIO	AM335X_GPIO1
#define S1_PIN (15)
#define S2_PIN (16)
#define S3_PIN (17)

void button_init() {
	//init of GPIO
	am335x_gpio_init(BTN_GPIO);
	//init of the buttons as Input
	am335x_gpio_setup_pin_in(BTN_GPIO, S1_PIN, AM335X_GPIO_PULL_NONE, 0);
	am335x_gpio_change_state(BTN_GPIO, S1_PIN, 1);
	am335x_gpio_setup_pin_in(BTN_GPIO, S2_PIN, AM335X_GPIO_PULL_NONE, 0);
	am335x_gpio_change_state(BTN_GPIO, S2_PIN, 1);
	am335x_gpio_setup_pin_in(BTN_GPIO, S3_PIN, AM335X_GPIO_PULL_NONE, 0);
	am335x_gpio_change_state(BTN_GPIO, S2_PIN, 1);
}


bool button_s1_is_pressed() {
	return !am335x_gpio_get_state(BTN_GPIO, S1_PIN);
}

bool button_s2_is_pressed() {
	return !am335x_gpio_get_state(BTN_GPIO, S2_PIN);
}
bool button_s3_is_pressed() {
	return !am335x_gpio_get_state(BTN_GPIO, S3_PIN);
}


