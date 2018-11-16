/**
 * Programmation C: Basics
 * solution to exercice 1
 */

#include <stdio.h>

static char msg[] = "plain text message";

char crypt (char c)
{
	if ((c >= 'a') && (c <= 'z')) {
		c += 5;
		if (c > 'z') c -= 'z' - 'a' + 1;
	}
	if ((c >= 'A') && (c <= 'Z')) {
		c += 5;
		if (c > 'Z') c -= 'Z' - 'A' + 1;
	}
	return c;
}

int main ()
{
	int i=0;
	printf ("before: %s\n", msg);
	char cmsg[sizeof(msg)];
	while (msg[i] != '\0') {
		cmsg[i]=crypt(msg[i]);
		i++;
	}
	cmsg[i]=0;
	printf ("after : %s\n", cmsg);

	return 0;
}
