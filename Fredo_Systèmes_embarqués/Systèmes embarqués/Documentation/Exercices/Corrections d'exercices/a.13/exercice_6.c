/**
 * C-Programming - Pointers
 * solution of exercice #6
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


struct elem {
	short value;
	struct elem *next;
};

struct result {
	short max;
	short min;
};

struct elem elems[8] = {
	{30, &elems[1]},
	{22, &elems[2]},
	{33, &elems[3]},
	{44, &elems[4]},
	{55, &elems[5]},
	{66, &elems[6]},
	{99, &elems[7]},
	{88, &elems[0]},
};


void compute_min_max (const struct elem *first, struct result *result)
{
	result->min=0;
	result->max=0;
	const struct elem* e = first;
	if (e != 0) {
		result->min = e->value;
		result->max = e->value;
		while (e->next != first) {
			e = e->next;
			if (result->min > e->value) result->min = e->value;
			if (result->max < e->value) result->max = e->value;
		}
	}
}

int main()
{
	printf ("C-Programming - Pointers: solution of exercice #6\n");

	struct result result;
	compute_min_max (&elems[0], &result);
	printf ("min=%d, max=%d\n", result.min, result.max);

	return 0;
}
