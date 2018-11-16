/**
 * C-Programming - Pointers
 * solution of exercice #5
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

char   str1[]="Programmation";
char   str2[]="Algorithmique";
char   str3[]="Microprocesseurs";
char   str4[]="Physique";
char*  tab[] = {str1, str2, str3, str4};
char** ptab = tab;

char* max_str (char**ptTab, int size)
{
	int len=0;
	char* str=0;
	while (size > 0) {
		size--;
		int i=0;
		while (ptTab[size][i] != 0) i++;
		if (i > len) {
			len = i;
			str = ptTab[size];
		}
	}
	return str;
}

int main()
{
	printf ("C-Programming - Pointers: solution of exercice #5\n");

	char* max = max_str(ptab, ARRAY_SIZE(tab));
	printf ("longest string=%s\n", max);

	return 0;
}
