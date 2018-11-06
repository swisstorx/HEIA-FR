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


/*
 * methode de parsing issu de la série d'exercice sur les pointeurs
 */
static void tokenize (char* s, int* argc, char** argv)
{
	*argc = 0;
	while (1) {
		while ((*s <= ' ') && (*s != '\0')) s++;
		if (*s == '\0') break;

		char quote = *s;
		if ((quote == '"') || (quote == '\'')) {
			s++;
			argv[(*argc)++] = s++;
			while ((*s != quote) && (*s != '\0')) s++;

		} else {
			argv[(*argc)++] = s++;
			while (*s > ' ') s++;
		}

		if (*s == '\0') break;

		*s++ = '\0';
	}
}
