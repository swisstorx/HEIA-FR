/**
 * Programmation C: Basics
 * solution to exercice 1
 */

#include <stdio.h>

#define SHIFT_LOWER	5
#define SHIFT_UPPER	9

static char msg[] = "a non encrypted message (abc-uvw-xyz )... "
					"and A SECOND NON CRYPTED MESSAGE (ABC-DEFGHIJKLMN-XYZ)...";

char crypt (char c)
{
	if ((c >= 'a') && (c <= 'z')) {
		c += SHIFT_LOWER;
		if (c > 'z') {
			c -= ('z' - 'a') + 1;
		}
	}
	if ((c >= 'A') && (c <= 'Z')) {
		c -= SHIFT_UPPER;
		if (c < 'A') {
			c += ('Z' - 'A') + 1;
		}
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
