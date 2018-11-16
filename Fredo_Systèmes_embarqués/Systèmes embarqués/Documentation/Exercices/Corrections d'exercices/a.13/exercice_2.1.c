/**
 * C-Programming - Pointers
 * solution of exercice #2 (round-robin list)
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
	if (*list == 0) {
		ele->next = ele;
	} else {
		ele->next = (*list)->next;
		(*list)->next = ele;
	}
	*list = ele;

	return 0;
}

static struct element* search_ele (int key, struct element* list)
{
	struct element* next = 0;
	if (list != 0) {
		next = list->next;
		while ((next != list) && (next->key != key)) next = next->next;
		if (next->key != key) next = 0;
	}

	return next;
}

static struct element* remove_ele (int key, struct element** list)
{
	struct element* ele = 0;
	if (*list != 0) {
		// test if only one element in the list
		if (*list == (*list)->next) {
			if ((*list)->key == key) *list = 0;
		} else {
			// multiple elements, look for matching key
			struct element* prev = *list;
			struct element* next = (*list)->next;
			while ((next != *list) && (next->key != key)) {
				prev = next;
				next = next->next;
			}
			if (next->key == key) {
				// element found
				prev->next = next->next;
				if (next == *list) *list = prev;
				ele = next;
			}
		}
	}
	return ele;
}

static int dump_list(struct element* list)
{
	if (list != 0) {
		struct element* next = list->next;
		do {
			printf("      key = %2d, value = %3d\n", next->key, next->value);
			next = next->next;
		} while (list != next);
	}

	return 0;
}


int main()
{
	struct element* list = 0;

	printf ("C-Programming - Pointers: solution of exercice #2 (Round-robing list)\n");

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
		if ((ele1 == 0) || (ele1->key != i)) printf ("error: ele %2d not found\n", i);
	}

	printf("  Remove all elements from the list...\n");
	while (list != 0) del_ele(remove_ele (list->key, &list));

	printf("    dump the list...\n");
	dump_list(list);

	return 0;
}
