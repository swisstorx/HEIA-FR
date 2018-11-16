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
	printf ("pa=%d\n", (int)pa);

	struct a_struct* pb = &pa[10];
	printf ("pb=%d\n", (int)pb);

	struct a_struct* pc = pa + 10;
	printf ("pc=%d\n", (int)pc);

	struct a_struct* pd = pc--;
	printf ("pc=%d, pd=%d\n", (int)pc, (int)pd);

	struct a_struct* pe = ++pb;
	printf ("pe=%d, pb=%d\n", (int)pe, (int)pb);

	return 0;
}
