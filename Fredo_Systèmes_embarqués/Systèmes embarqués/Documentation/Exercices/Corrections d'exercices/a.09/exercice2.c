/**
 * Programmation C: Basics
 * solution to exercice 2
 */

#include <stdio.h>
#include <stdbool.h>

static char str1[] = "open	arg1   arg2 arg3";
static char str2[] = "closse	    param1     param2	  ";
static char str3[] = "   read p1";
static char str4[] = "write a1	   a2	a3   \t	  a4		     ";

void tokenize (char str[])
{
	char* argv[20];
	int   argc = 0;

	printf("  line	   = \"%s\"\n", str);
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

	printf("  token[%d] = ", argc);
	for (int i = 0; i < argc; i++) printf("\"%s\" ", argv[i]);
	printf("\n\n");
}

int main()
{
	tokenize (str1);
	tokenize (str2);
	tokenize (str3);
	tokenize (str4);

	return 0;
}
