/**
 * C-Programming - Pointers
 * solution of exercice #2 (double linked list)
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NB_OF_ELES 12

struct element {
	int key;
	int value;
	struct element* next;
	struct element* prev;
};

static struct element* new_ele (int key, int value)
{
	struct element* ele = calloc (1, sizeof(*ele));
	if (ele != 0) {
		ele->key = key;
		ele->value = value;
	}
	return ele;
}

static void del_ele (struct element* ele)
{
	if (ele != 0) free (ele);
}

static int insert_ele (struct element* ele, struct element** list)
{
	struct element* prev = 0;
	struct element* next = *list;
	while ((next != 0) && (next->key < ele->key)) {
		prev = next;
		next = next->next;
	}

	ele->prev = 0;
	ele->next = 0;
	if (prev == 0) {
		ele->next = *list;
		*list = ele;
		if (ele->next != 0) ele->next->prev = ele;
	} else {
		ele->next = prev->next;
		prev->next = ele;

		ele->prev = prev;
		if (ele->next != 0) ele->next->prev = ele;
	}

	return 0;
}


static struct element* search_ele (int key, struct element* list)
{
	struct element* next = list;
	while ((next != 0) && (next->key != key)) next = next->next;

	return next;
}

static struct element* remove_ele (int key, struct element** list)
{
	struct element* ele = search_ele(key, *list);
	if (ele != 0) {
		if (ele->next != 0) {
			ele->next->prev = ele->prev;
		}
		if (ele->prev == 0) {
			*list = ele->next;
		} else {
			ele->prev->next = ele->next;
		}
	}

	return ele;
}

static int dump_list(struct element* list)
{
	struct element* next = list;
	while (next != 0) {
		printf("      key = %2d, value = %3d\n", next->key, next->value);
		next = next->next;
	}

	return 0;
}


int main()
{
	struct element* list = 0;

	printf ("C-Programming - Pointers: solution of exercice #2 (Double linked list)\n");

	printf("  Create %d elements...\n",NB_OF_ELES);
	for (int i=0;i<NB_OF_ELES;i+=2) {
		insert_ele (new_ele (i, i*i), &list);
	}
	for (int i=1;i<NB_OF_ELES;i+=2) {
		insert_ele (new_ele (i, i*i), &list);
	}
	printf("    dump the list...\n");
	dump_list(list);

	for (int i=0; i<NB_OF_ELES;i++) {
		struct element* ele1 = search_ele (i, list);
		if ((ele1 == 0) || (ele1->key != i)) printf ("error: ele %d not found\n", i);
	}

	printf("  Remove all elements...\n");
	while (list != 0) del_ele(remove_ele (list->key, &list));

	printf("    dump the list...\n");
	dump_list(list);

	return 0;
}
