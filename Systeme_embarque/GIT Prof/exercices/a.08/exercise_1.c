/**
 * Programmation C: Pointeurs de fonction
 * solution de l'exercice 1
 *
 *   simple command line interpreter based on string parsing and using
 *   fonction pointers to process commands
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define ARRAY_SIZE(x)(sizeof(x)/sizeof(x[0]))

struct command {
	const char* name;
	const char* brief;
	const char* help;
	int (*cmd) (int argc, char* argv[]) ;
	struct command* next;
};

static struct command* cmd_list = 0;

// ---------------------------------------------------------------------------------------

static void tokenize (char* str, int* argc, char** argv, int sz)
{
	*argc = 0;
	while (1) {
		while ((*str <= ' ') && (*str != '\0')) str++;
		if (*str == '\0') break;

		argv[(*argc)++] = str++;
		if (*argc >= sz) break;

		while (*str > ' ') str++;
		if (*str == '\0') break;

		*str++ = '\0';
	}
}

// ---------------------------------------------------------------------------------------

int attach (struct command* cmd)
{
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

int process (const char* command_line)
{
	int status = -1;
	char str[strlen(command_line)+1];
	char* argv[100] = {""};
	int   argc = 0;

	strcpy (str, command_line);
	tokenize (str, &argc, &argv[0], ARRAY_SIZE(argv));

	const struct command *cmd = cmd_list;
	while ((cmd != 0) && (strcmp (argv[0], cmd->name) != 0)) {
		cmd = cmd->next;
	}
	if (cmd != 0) {
		status = cmd->cmd (argc, argv);
		if (status != 0) {
			printf ("error on processing: %d\n", status);
		}
	} else {
		printf ("error: command not found: \"%s\"\n", argv[0]);
	}
	return status;
}


// ---------------------------------------------------------------------------------------

static int command1 (int argc, char* argv[])
{
	printf("command1");
	for (int i = 1; i < argc; i++) {
		printf(" %s", argv[i]);
	}
	printf("\n");
	return 0;
}
static struct command cmd1 = {
	.name = "command1",
	.brief ="b1",
	.help="c1",
	.cmd = command1,
};

// ---------------------------------------------------------------------------------------

static int command2 (int argc, char* argv[])
{
	printf("command2");
	for (int i = 1; i < argc; i++) {
		printf(" %s", argv[i]);
	}
	printf("\n");
	return 0;
}
static struct command cmd2 = {
	.name = "command2",
	.brief ="b2",
	.help="c2",
	.cmd = command2,
};

// ---------------------------------------------------------------------------------------

static int command3 (int argc, char* argv[])
{
	int status = -1;
	if (argc == 4) {
		int i = atoi (argv[1]);
		float e = atof (argv[2]);
		float f = atof (argv[3]);
		printf("%s %d %F %e\n", argv[0], i,e,f);
		status = 0;
	}
	return status;
}
static struct command cmd3 = {
	.name = "command3",
	.brief ="b3",
	.help="c3",
	.cmd = command3,
};

// ---------------------------------------------------------------------------------------

static int command4 (int argc, char* argv[])
{
	printf("command4");
	for (int i = 1; i < argc; i++) {
		printf(" %s", argv[i]);
	}
	printf("\n");
	return 0;
}
static struct command cmd4 = {
	.name = "command4",
	.brief ="b4",
	.help="c4",
	.cmd = command4,
};

// ---------------------------------------------------------------------------------------

static const char str1[] = "command1   10   20 30";
static const char str2[] = "command2     10     un_string     ";
static const char str3[] = "command3 30 40.20 50e-2";
static const char str4[] = "command4 ";
static const char str5[] = "unsupported";
static const char str6[] = "";

// ---------------------------------------------------------------------------------------

int main()
{
	attach (&cmd3);
	attach (&cmd1);
	attach (&cmd2);
	attach (&cmd4);

	struct command* e = cmd_list;
	while (e != 0) {
		printf ("%s - %s - %s - %p\n", e->name, e->brief, e->help, e->cmd);
		e = e->next;
	}
	printf ("\n");

	process (str1);
	process (str2);
	process (str3);
	process (str4);
	process (str5);
	process (str6);

	return 0;
}
