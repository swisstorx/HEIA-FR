/*
 * cli.c
 *
 *  Created on: Nov 5, 2018
 *      Author: lmi
 */

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <getopt.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "cli.h"
#include "am335x_console.h"
#define CR   '\r'
int numb = 0;
char buffer[50];
static struct command* cmd_list = 0;
struct command {
	const char* name;
	const char* brief;
	const char* help;
	int (*cmd)(int argc, char* argv[]);
	struct command* next;
};

static int handle_command(const char* str) {
	char s[strlen(str) + 1];
	char* argv[20] = { "" };
	int argc = 0;

	strcpy(s, str);

	tokenize(s, &argc, &argv[0]);

	struct command *cmd = cmd_list;
	while ((cmd != 0) && (strcmp(argv[0], cmd->name) != 0)) {
		cmd = cmd->next;
	}
	if (cmd != 0) {
		cmd->cmd(argc, argv);
	} else if (argc > 0) {
		printf("error: command not found: \"%s\"\n", argv[0]);
	}
	return argc > 0 ? 0 : -1;
}

/*
 * methode de parsing issu de la série d'exercice sur les pointeurs
 */
extern void tokenize(char* s, int* argc, char** argv) {
	*argc = 0;
	while (1) {
		while ((*s <= ' ') && (*s != '\0'))
			s++;
		if (*s == '\0')
			break;

		char quote = *s;
		if ((quote == '"') || (quote == '\'')) {
			s++;
			argv[(*argc)++] = s++;
			while ((*s != quote) && (*s != '\0'))
				s++;

		} else {
			argv[(*argc)++] = s++;
			while (*s > ' ')
				s++;
		}

		if (*s == '\0')
			break;

		*s++ = '\0';
	}
}

extern void cli_init() {
	am335x_console_init();
	numb = 0;
}
//static void append(){
//
//}
extern void cli_probe() {
	if (am335x_console_tstc()) {
		char c = am335x_console_getc();

		if (c == 13) { //13 = code pour le retour à la ligne
			am335x_console_putc(c);
			handle_command(&c);

		} else {
			am335x_console_putc(c);
			buffer[numb] = am335x_console_getc();
			numb++;
		}

	}
}
