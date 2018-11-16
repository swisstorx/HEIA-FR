/**
 * Programmation C: Fonctions
 * solution de l'exercice 1
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

static char str1[] = "command1   10   20 30";
static char str2[] = "command2     10     un_string     ";
static char str3[] = "command3 30 40.20 50e-2";
static char str4[] = "command4 ";

static int command1 (int argc, char* argv[])
{
	printf(" --> command1");
	for (int i = 1; i < argc; i++) {
		printf(" %s", argv[i]);
	}
	printf("\n");
	return 0;
}

static int command2 (int argc, char* argv[])
{
	printf(" --> command2");
	for (int i = 1; i < argc; i++) {
		printf(" %s", argv[i]);
	}
	printf("\n");
	return 0;
}

static int command3 (int argc, char* argv[])
{
	int status = -1;
	if (argc == 4) {
		int i = atoi (argv[1]);
		float e = atof (argv[2]);
		float f = atof (argv[3]);
		printf(" --> %s %d %F %e\n", argv[0], i,e,f);
		status = 0;
	}
	return status;
}

static int command4 (int argc, char* argv[])
{
	printf(" --> command4");
	for (int i = 1; i < argc; i++) {
		printf(" %s", argv[i]);
	}
	printf("\n");
	return 0;
}

void tokenize (char str[])
{
	char* argv[20];
	int   argc = 0;

	printf("line	   = \"%s\"\n", str);
	int i = 0;
	while (1) {
		while ((str[i] <= ' ') && (str[i] != '\0')) i++;	
		if (str[i] == '\0') break;

		argv[argc] = &str[i];
		argc++;

		while (str[i] > ' ') i++;
		if (str[i] == '\0') break;

		str[i] = '\0';
		i++;
	}

	int status = -1;
	if (strcmp (argv[0], "command1") == 0) status = command1 (argc, argv);
	if (strcmp (argv[0], "command2") == 0) status = command2 (argc, argv);
	if (strcmp (argv[0], "command3") == 0) status = command3 (argc, argv);
	if (strcmp (argv[0], "command4") == 0) status = command4 (argc, argv);
	if (status != 0) printf ("error %d\n", status);
}


int main()
{
	tokenize (str1);
	tokenize (str2);
	tokenize (str3);
	tokenize (str4);

	return 0;
}
