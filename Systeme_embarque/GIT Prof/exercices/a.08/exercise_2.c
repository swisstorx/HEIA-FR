/**
 * Programmation C: Pointeurs de fonction
 * solution de l'exercice 2
 */

#include <stdio.h>

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

typedef int (*operation_t) (int*, int);

int fnct_a (int *ptr, int max) {return *ptr + max + 100; }
int fnct_b (int *ptk, int min) {return *ptk + min + 200; }
int fnct_c (int *trd, int moy) {return *trd + moy + 300; }
int fnct_d (int *utr, int val) {return *utr + val + 400; }

operation_t tableau[] = {fnct_a, fnct_b, fnct_c, fnct_d};

int main()
{
	printf ("Programmation C: Pointeurs de fonction: solution de l'exercice #2\n");
	for (unsigned i=0; i<ARRAY_SIZE(tableau); i++) {
		int ret = i+10;
		int j = tableau[i] (&ret, i);
		printf ("i=%d, ret=%d, j=%d\n", i, ret, j);
	}

	return 0;
}
