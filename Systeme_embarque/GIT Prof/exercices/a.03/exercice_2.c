/**
 * Programmation C: Basics
 * solution to exercice 2
 */

#include <stdio.h>
#include <string.h>

#define SHIFT_LOWER	5
#define SHIFT_UPPER	9

static char msg[] = "a non encrypted message (abc-uvw-xyz )... "
					"and A SECOND NON CRYPTED MESSAGE (ABC-DEFGHIJKLMN-XYZ)...";

/**
 * encryption function
 */
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


/**
 * decryption function
 */
char decrypt (char c)
{
	if ((c >= 'a') && (c <= 'z')) {
		c -= SHIFT_LOWER;
		if (c < 'a') {
			c += ('z' - 'a') + 1;
		}
	} else if ((c >= 'A') && (c <= 'Z')) {
		c += SHIFT_UPPER;
		if (c > 'Z') {
			c -= ('Z' - 'A') + 1;
		}
	}
	return c;
}


int main()
{
	char crypted[sizeof(msg)]   = {[0]=0,};
	char uncrypted[sizeof(msg)] = {[0]=0,};

	for (unsigned i=0; i<sizeof(msg); i++) {
		crypted[i]   = crypt (msg[i]);
	}

	for (unsigned i=0; i<strlen(crypted); i++) {
		uncrypted[i] = decrypt (crypted[i]);
	}

	printf ("message  =\"%s\"\n", msg);
	printf ("crypted  =\"%s\"\n", crypted);
	printf ("uncrypted=\"%s\"\n", uncrypted);
	printf ("result=%s\n", strcmp (uncrypted, msg)==0 ? "ok" : "nok");

	return 0;
}
