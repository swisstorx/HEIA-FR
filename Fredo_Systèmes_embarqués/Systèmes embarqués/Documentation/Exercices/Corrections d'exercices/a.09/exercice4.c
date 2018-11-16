/**
 * Programmation C: Basics
 * solution to exercice 4
 */

#include <stdio.h>

unsigned char i;
unsigned int  res;
const unsigned char nbr = 5;

int main()
{
	i = 0;
	res = 0;
	while (i < nbr)	res += i++;

	printf ("res=%d, i=%d, nbr=%d\n", res, i, nbr);

	return 0;
}
