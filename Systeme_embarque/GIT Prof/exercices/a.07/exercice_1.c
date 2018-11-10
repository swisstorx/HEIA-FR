/**
 * C-Programming - Pointers
 * solution of exercice #3
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct a_struct {int a; int b; int c;};

int main()
{
	printf ("Programmation C: Pointeurs: solution de l'exercice #1\n");

	struct a_struct* pa = (struct a_struct*) 1000;
	printf ("pa=%ld\n", (long)pa);

	struct a_struct* pb = &pa[10];
	printf ("pb=%ld\n", (long)pb);

	struct a_struct* pc = pa + 10;
	printf ("pc=%ld\n", (long)pc);

	struct a_struct* pd = pc--;
	printf ("pc=%ld, pd=%ld\n", (long)pc, (long)pd);

	struct a_struct* pe = ++pb;
	printf ("pe=%ld, pb=%ld\n", (long)pe, (long)pb);

	return 0;
}
