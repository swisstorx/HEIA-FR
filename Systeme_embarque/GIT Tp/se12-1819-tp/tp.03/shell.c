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
 * Abstract: shell
 *
 * Purpose:
 *
 * Origin:
 *
 * Author: 	Sven Rouvinez / Marc Roten
 * Date: 	09.12.2018
 */
#include "shell.h"
#include <stdbool.h>
#include <am335x_console.h>
#include <string.h>
#include "display.h"
#include "cli.h"

#define ARRAY_SIZE(x)(sizeof(x)/sizeof(x[0]))

static char buffer[10000];

static struct command* cmd_list = 0;

void shell_init() {
	attach(&cmd1);
	attach(&cmd2);
}

void shell_probe() {
	probe();
}

// ---------------------------------------------------------------------------------------

static void tokenize(char* str, int* argc, char** argv, int sz) {
	*argc = 0;
	while (1) {
		while ((*str <= ' ') && (*str != '\0'))
			str++;
		if (*str == '\0')
			break;

		argv[(*argc)++] = str++;
		if (*argc >= sz)
			break;

		while (*str > ' ')
			str++;
		if (*str == '\0')
			break;

		*str++ = '\0';
	}
}

// ---------------------------------------------------------------------------------------

int attach(struct command* cmd) {
	int status = 0;
	struct command* e = cmd_list;
	struct command* p = 0;
	while ((e != 0) && (strcmp(e->name, cmd->name) < 0)) {
		p = e;
		e = e->next;
	}
	if (p == 0) {
		cmd->next = cmd_list;
		cmd_list = cmd;
	} else {
		cmd->next = e;
		p->next = cmd;
	}
	return status;
}

// ---------------------------------------------------------------------------------------

int process(const char* command_line) {
	int status = -1;
	char str[strlen(command_line) + 1];
	char* argv[100] = { "" };
	int argc = 0;

	strcpy(str, command_line);
	tokenize(str, &argc, &argv[0], ARRAY_SIZE(argv));

	const struct command *cmd = cmd_list;
	while ((cmd != 0) && (strcmp(argv[0], cmd->name) != 0)) {
		cmd = cmd->next;
	}
	if (cmd != 0) {
		status = cmd->cmd(argc, argv);
		if (status != 0) {
			printf("error on processing: %d\n", status);
		}
	} else {
		printf("error: command not found: \"%s\"\n", argv[0]);
	}
	return status;
}

void probe() {
	static int i = 0;
	if (am335x_console_tstc()) {
		char c = am335x_console_getc();
		switch (c) {
		case '\n':
		case '\r':
			buffer[i] = 0;
			printf("\nline (%d):%s\n", strlen(buffer), buffer);
			process(buffer);
			i = 0;
			break;
		case '\b':
			if (i > 0)
				i--;
			am335x_console_putc('\b');
			am335x_console_putc(' ');
			am335x_console_putc('\b');
			break;
		default:
			am335x_console_putc(c);
			buffer[i++] = c;
		}
	}
}
