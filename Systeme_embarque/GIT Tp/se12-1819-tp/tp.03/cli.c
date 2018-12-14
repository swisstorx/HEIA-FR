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
 * Abstract: Thermo CLI
 *
 * Purpose:
 *
 * Origin:
 *
 * Author: 	Sven Rouvinez / Marc Roten
 * Date: 	10.12.2018
 */
#include "cli.h";
#include "shell.h";

int thermoInfoInit(int argc, char* argv[]) {
	thermo_info_init(argc, argv);
	return 0;
}

int thermoChangeColor(int argc, char* argv[]) {
	thermo_change_color(argc, argv);
	return 0;
}

extern struct command cmd1 = { .name = "command1", .brief = "b3", .help = "c3",
		.cmd = thermoInfoInit, };

extern struct command cmd2 = { .name = "command2", .brief = "b3", .help = "c3",
		.cmd = thermoChangeColor, };

