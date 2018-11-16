/**
 * Programmation C: Structures complexes
 * solution de l'exercice 3
 */
#include <stdio.h>
#include "nombre.h"
#include "opp.h"

#define print(x) printf (#x".real=%-3ld - "#x".imag=%-3ld\n",x.real, x.imag);

int main()
{
	struct complex s1 = {20, 65};
	struct complex s2 = {56, 12};
	
	struct complex s3 = addi(&s1, &s2);
	struct complex s4 = subs(&s1, &s2);
	
	print(s1);
	print(s2);
	print(s3);
	print(s4);

	return 0;
}

