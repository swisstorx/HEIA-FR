/**
 * C-Programming - Pointers
 * solution of exercice #3
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

struct elem {
	char name[100];
	struct elem* next;
};


struct container {
	struct elem* first;
	struct elem* last;
};

/**
 * fonction capable de compter le nombre d’éléments
 * @param chaine pointeur sur la structure chaine
 * @return nombre d’éléments
 */
int get_nb_of_eles (const struct container *container)
{
	int eles = 0;
	if ((container != 0) && (container->first != 0)) {
		struct elem* ele = container->first;
		do {
			eles++;
			ele = ele->next;
		} while (container->first != ele);
	}
	return eles;
}

/**
 * fonction capable d’enlever un élément sans casser la chaîne
 * @param chaine pointeur sur la structure chaine
 * @param index position dans la chaîne
 */
struct elem* extract (struct container *container, int index)
{
	struct elem* ele = 0;
	if ((container != 0) && (container->first != 0)) {
		if (container->first == container->last) {
			ele = container->first;
			container->first = 0;
			container->last = 0;
		} else {
			struct elem* e = container->first;
			struct elem* p = container->last;
			for (int i=index; i>0; i--) {
				p = e;
				e = e->next;
			}
			p->next = e->next;
			ele = e;
			if (e==container->last)  container->last = p;
			if (e==container->first) container->first = e->next;
		}
	}
	return ele;
}

struct elem eles[] = {
	[0] = {.name = "a", .next = &eles[1], },
	[1] = {.name = "b", .next = &eles[2], },
	[2] = {.name = "c", .next = &eles[3], },
	[3] = {.name = "d", .next = &eles[4], },
	[4] = {.name = "e", .next = &eles[0], },
};

struct container container = {.first = &eles[0], .last = &eles[4]};


int main()
{
	printf ("C-Programming - Pointers: solution of exercice #3\n");

	for (unsigned i=0; i<ARRAY_SIZE(eles); i++) {
		printf ("eles[%i/%p].name=%s, .next=%p\n",
			i, &eles[i], eles[i].name, eles[i].next);
	}
	printf ("chaine.first=%p, .last=%p\n", container.first, container.last);
	for (int i=9; i>=0; i--) {
		printf ("[%d]: nb of eles=%d\n", i, get_nb_of_eles (&container));
		struct elem* e = container.first;
		if (e != 0) {
			do {
				printf ("     ele.name=%s, .next=%p\n",
					e->name, e->next);
				e = e->next;
			} while (e != container.first);
		}
		e=extract (&container, i);
		if (e != 0) printf ("     ele.name=%s extracted\n", e->name);
	}

	return 0;
}
