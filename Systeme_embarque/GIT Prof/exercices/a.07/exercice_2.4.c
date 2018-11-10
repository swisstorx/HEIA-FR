/**
 * C-Programming - Pointers
 * solution of exercice #2 (map with a binary-search)
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAP_LEN 20

struct element {
	int key;
	int value;
};

static struct element* map[MAP_LEN];

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


static int search_ele (int key, struct element** map)
{
	int l = -1;
	int r = MAP_LEN;
	while (r - l > 1) {
		int m = (l + r) / 2;
		if ((map[m] != 0) && (map[m]->key < key))
			l = m;
		else
			r = m;
	}
	if ((map[r] == 0) || (map[r]->key != key)) r = -r-1;
	return r;
}

static int insert_ele (struct element* ele, struct element** map)
{
	int index = search_ele (ele->key, map);
	if (index < 0) {
		memmove (&map[-index], &map[-index-1], sizeof(struct element*)*(MAP_LEN+index));
		map[-index-1]=ele;
	}

	return 0;
}

static struct element* remove_ele (int key, struct element** map)
{
	struct element* ele=0;
	int index = search_ele (key, map);
	if (index >= 0) {
		ele = map[index];
		memcpy (&map[index], &map[index+1], sizeof(struct element*)*(MAP_LEN+index-1));
		map[MAP_LEN-1]=0;
	}

	return ele;
}

static void dump_list(struct element** map)
{
	for (int index=0; index < MAP_LEN; index++) {
		if (map[index] != 0) {
			printf("      [%2d] ele.key = %2d, ele.value = %3d\n", index, map[index]->key, map[index]->value);
		}
	}
}


int main()
{
	printf ("C-Programming - Pointers: solution of exercice #2 (Map (binary search) list)\n");

	printf("  Create %d elements...\n",MAP_LEN);
	for (int i=1;i<MAP_LEN;i+=2) {
		insert_ele (new_ele (i, i*i), map);
	}
	for (int i=0;i<MAP_LEN;i+=2) {
		insert_ele (new_ele (i, i*i), map);
	}
	printf("    dump the list...\n");
	dump_list(map);

	for (int i=0; i<MAP_LEN;i++) {
		int index = search_ele (i, map);
		if ((index < 0) || (map[index]->key != i)) printf ("error: ele %d not found\n", i);
	}

	printf("  Remove all elements from the list...\n");
	while (map[0] != 0)
	{
		del_ele(remove_ele (map[0]->key, map));
	}

	printf("    dump the list...\n");
	dump_list(map);

	return 0;
}
