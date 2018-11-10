/**
 * C-Programming - Pointers
 * solution of exercice #2 (single linked list)
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
	struct element* ele = calloc (1, sizeof(struct element));
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

static int insert_fifo_ele (struct element* ele, struct element** list)
{
	ele->next = 0;
	if (*list == 0) {
		*list = ele;
	} else {
		struct element* next = *list;
		while (next->next != 0) next = next->next;
		next->next = ele;
	}

	return 0;
}


static int insert_lifo_ele (struct element* ele, struct element** list)
{
	ele->next = *list;
	*list = ele;

	return 0;
}

static int insert_sorted_ele (struct element* ele, struct element** list)
{
	struct element* prev = 0;
	struct element* next = *list;
	while ((next != 0) && (next->key < ele->key)) {
		prev = next;
		next = next->next;
	}

	ele->next = 0;
	if (prev == 0) {
		ele->next = *list;
		*list = ele;
	} else {
		ele->next = prev->next;
		prev->next = ele;
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
	struct element* prev = 0;
	struct element* next = *list;
	while ((next != 0) && (next->key != key)) {
		prev = next;
		next = next->next;
	}

	if (next != 0) {
		if (prev == 0) {
			*list = next->next;
		} else {
			prev->next = next->next;
		}
	}

	return next;
}

static int dump_list(struct element* list)
{
	struct element* next = list;
	while (next != 0) {
		printf("        key = %2d, value = %3d\n", next->key, next->value);
		next = next->next;
	}

	return 0;
}


int main()
{
	struct element* fifo_list = 0;
	struct element* lifo_list = 0;
	struct element* sorted_list = 0;

	printf ("C-Programming - Pointers: solution of exercice #2 (Single linked list)\n");

	printf("  Create %d elements for each list type...\n",NB_OF_ELES);
	for (int i=0;i<NB_OF_ELES;i+=2) {
		insert_fifo_ele (new_ele (i, i*i), &fifo_list);
		insert_lifo_ele (new_ele (i, i*i), &lifo_list);
		insert_sorted_ele (new_ele (i, i*i), &sorted_list);
	}
	for (int i=1;i<NB_OF_ELES;i+=2) {
		insert_fifo_ele (new_ele (i, i*i), &fifo_list);
		insert_lifo_ele (new_ele (i, i*i), &lifo_list);
		insert_sorted_ele (new_ele (i, i*i), &sorted_list);
	}
	printf("    dump the lists...\n");
	printf("      fifo...\n");
	dump_list(fifo_list);
	printf("      lifo...\n");
	dump_list(lifo_list);
	printf("      sorted...\n");
	dump_list(sorted_list);

	for (int i=0; i<NB_OF_ELES;i++) {
		struct element* ele1 = search_ele (i, fifo_list);
		struct element* ele2 = search_ele (i, lifo_list);
		struct element* ele3 = search_ele (i, sorted_list);
		if ((ele1 == 0) || (ele2 == 0) || (ele3 == 0)) printf ("error: ele %d not found\n", i);
	}

	printf("  Remove all elements from the lists...\n");
	while (fifo_list != 0)   del_ele(remove_ele (fifo_list->key, &fifo_list));
	while (lifo_list != 0)   del_ele(remove_ele (lifo_list->key, &lifo_list));
	while (sorted_list != 0) del_ele(remove_ele (sorted_list->key, &sorted_list));

	printf("    dump the list...\n");
	dump_list(fifo_list);
	dump_list(lifo_list);
	dump_list(sorted_list);

	return 0;
}
