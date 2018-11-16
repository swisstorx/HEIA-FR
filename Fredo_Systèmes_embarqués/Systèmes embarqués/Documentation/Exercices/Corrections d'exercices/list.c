#include <stdio.h>
#include <stdlib.h>

struct element {
	int key;
	int value;
	struct element * next;
};

static struct element* new_ele(int key, int value)
{
	struct element* e = calloc(1, sizeof(*e));
	if (e != 0) {
		e->key = key;
		e->value = value;
	}
	return e;
}

static void* del_ele(struct element* e)
{
	if (e != 0) free(e);
	return 0;
}

static int insert_filo (struct element* e, struct element* *list)
{
	e->next = *list;
	*list = e;
	return 0;
}

static struct element* search (int key, struct element* list)
{
	while ((list != 0) && (list->key != key))
		list = list->next;
	return list;
}

static struct element* extract (int key, struct element* *list)
{
	struct element* e = *list;
	struct element* p = 0;
	while ((e != 0) && (e->key != key)) {
		p = e;
		e = e->next;
	}
	if (e != 0) {
		if (p == 0) {
			*list = e->next;
		} else {
			p->next = e->next;
		}
		e->next = 0;
	}
	return e;
}

static void dump_list(struct element* list)
{
	while (list!=0) {
		printf ("element(%p): key=%d, value=%d\n", list, list->key, list->value);
		list = list->next;
	}
}

int main()
{
	struct element* list = 0;

	for (int i = 0; i< 10; i++)  {
		struct element * e = new_ele(i,i+10);
		insert_filo (e, &list);
	}
	dump_list (list);

	struct element* e = search (1, list);
	printf ("search(1): element(%p): key=%d, value=%d\n", e, e->key, e->value);

	while (list != 0) {
		del_ele(extract (list->key, &list));
	}
	dump_list (list);


	return 0;
}