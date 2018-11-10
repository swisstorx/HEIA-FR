/**
 * C-Programming - Pointers
 * solution of exercice #4
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))


struct node {
	unsigned char ident;
	long          size;
	struct node*  next;
};

/**
 * fonction capable de compter le nombre d’éléments
 *@param list pointeur sur le premier élément de la chaine
 *@param id identification de l’élément à rechercher (champ ident de la structure)
 *@return référence sur la structure recherchée en cas de succès et null (0) si aucun
 *        élément n’a été découvert
 */
struct node* search (struct node *list, unsigned char id)
{
	struct node* e = list;
	while ((e!=0) && (e->ident != id)) e=e->next;
	return e;
}

struct node nodes[8] = {
	{11, 10, &nodes[1]},
	{22, 20, &nodes[2]},
	{33, 30, &nodes[3]},
	{44, 40, &nodes[4]},
	{55, 50, 0},
	{66, 0, 0},
	{77, 0, 0},
	{88, 0, 0},
};

struct node* list = &nodes[0];

int main()
{
	printf ("C-Programming - Pointers: solution of exercice #4\n");

	printf ("show node table...\n");
	for (unsigned i=0; i<ARRAY_SIZE(nodes); i++) {
		printf ("  nodes[%i/%p].ident=%d, .size=%-2ld, .next=%p\n",
			i, &nodes[i], nodes[i].ident, nodes[i].size, nodes[i].next);

	}
	printf ("show node list...\n");
	struct node* node = list;
	while (node != 0) {
		printf ("  nodes[%p].ident=%d, .size=%ld, .next=%p\n",
			node, node->ident, node->size, node->next);
		node = node->next;
	}
	printf ("search all elements..\n");
	for (int i=ARRAY_SIZE(nodes)-1; i>=0; i--) {
		struct node* node = search (list, nodes[i].ident);
		printf ("  [%d]: search ident=%d/%p, next=%p\n",
		i, nodes[i].ident, &nodes[i], node);
	}

	return 0;
}
