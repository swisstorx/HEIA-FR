/**
 * Programmation C: Pointeurs de fonction
 * solution de l'exercice 3
 */

#include <stdio.h>

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

typedef int (*fnct_t) (int);

static int f1 (int a) { return 25 + (3 * a); }
static int f2 (int a) { return 192 - a; }
static int f3 (int a) { return a - 100; }
static int f4 (int a) { return a % 8; }

static fnct_t tabf[] = {f1, f2, f3, f4};

static int fnct(int x)
{
	unsigned k = (x >> 6) % ARRAY_SIZE(tabf);
	printf (" (f%d)", k+1);
	return tabf[k](x);
}

int main()
{
	printf ("Programmation C: Pointeurs de fonction: solution de l'exercice #3\n");

	int in[] = {10, 90, 120, 160, 180, 250};
	int out[ARRAY_SIZE(in)];

	for(unsigned i=0; i<ARRAY_SIZE(in); i++) {
		printf ("out[%d]", i);
		out[i]=fnct(in[i]);
		printf (" = %d\n", out[i]);
	}

	return 0;
}
