/**
 * Programmation C: Pointeurs de fonction
 * solution de l'exercice 2
 */

#include <stdio.h>

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

typedef int (*operation_t) ();

int fnct_a (int *ptr, int max) {printf("AAAAA\n");}
int fnct_b (int *ptk, int min) {printf("BBBBB\n");}
int fnct_c (int *trd, int moy) {printf("CCCCC\n");}
int fnct_d (int *utr, int val) {printf("DDDDD\n");}

operation_t tableau[] = {fnct_a, fnct_a, fnct_c, fnct_d};

int main()
{
	printf ("Programmation C: Pointeurs de fonction: solution de l'exercice #2\n");
	for (unsigned i=0; i<ARRAY_SIZE(tableau); i++) {
		int ret = i+10;
		int j = tableau[i] ();
	}

	return 0;
}
