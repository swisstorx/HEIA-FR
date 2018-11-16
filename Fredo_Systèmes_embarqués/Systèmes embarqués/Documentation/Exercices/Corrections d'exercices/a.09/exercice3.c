/**
 * Programmation C: Basics
 * solution to exercice 3
 */

#include <stdio.h>
#include <string.h>

#define DECAL_MIN	5
#define DECAL_MAJ	9

/**
 * encryption function
 */
char crypt (char p) {

	if ((p >= 'a') && (p <= 'z')) {
		p += DECAL_MIN;
		if (p > 'z') {
			p -= 26;
		}
	} else if ((p >= 'A') && (p <= 'Z')) {
		p -= DECAL_MAJ;
		if (p < 'A') {
			p += 26;
		}
	}
	return p;
}


/**
 * decryption function
 */
char decrypt (char c) {

	if ((c >= 'a') && (c <= 'z')) {
		c -= DECAL_MIN;
		if (c < 'a') {
			c += 26;
		}
	} else if ((c >= 'A') && (c <= 'Z')) {
		c += DECAL_MAJ;
		if (c > 'Z') {
			c -= 26;
		}
	}
	return c;
}


int main()
{
	char message[] = "a non encrypted message (uvwxyz )... and A SECOND CRYPTED MESSAGE (ABCDEFGHIJKLMN)...";
	char crypted[100]   = {[0]=0,};
	char uncrypted[100] = {[0]=0,};

	for (int i=0; i<100; i++) {
		crypted[i]   = crypt (message[i]);
	}

	for (int i=0; i<100; i++) {
		uncrypted[i] = decrypt (crypted[i]);
	}

	printf ("message  =\"%s\"\n", message);
	printf ("crypted  =\"%s\"\n", crypted);
	printf ("uncrypted=\"%s\"\n", uncrypted);
	printf ("result=%s\n", strcmp (uncrypted, message)==0 ? "ok" : "nok");

	return 0;
}
