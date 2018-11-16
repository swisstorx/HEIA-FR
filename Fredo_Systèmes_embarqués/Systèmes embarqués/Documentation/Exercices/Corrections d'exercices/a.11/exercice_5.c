/**
 * Programmation C: Structures complexes
 * solution de l'exercice 5
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct struct1 {
	char  attr1;
	short attr2;
	char  attr3;
	long  attr4;
	short attr5;
	long  attr6;
};

struct struct2 {
	char  attr1;
	short attr2;
	char  attr3;
	long  attr4;
	short attr5;
	long  attr6;
} __attribute__((__packed__));

struct struct3 {
	char  attr1;
	char  dummy1;
	short attr2;
	char  attr3;
	char  dummy2;
	char  dummy3;
	char  dummy4;
	long  attr4;
	short attr5;
	char  dummy5;
	char  dummy6;
	long  attr6;
};


int main()
{
	printf ("Offsets\n");
	printf (" attr1: %2zu %2zu %2zu\n",
		offsetof(struct struct1, attr1),
		offsetof(struct struct2, attr1),
		offsetof(struct struct3, attr1));
	printf (" attr2: %2zu %2zu %2zu\n",
		offsetof(struct struct1, attr2),
		offsetof(struct struct2, attr2),
		offsetof(struct struct3, attr2));
	printf (" attr3: %2zu %2zu %2zu\n",
		offsetof(struct struct1, attr3),
		offsetof(struct struct2, attr3),
		offsetof(struct struct3, attr3));
	printf (" attr4: %2zu %2zu %2zu\n",
		offsetof(struct struct1, attr4),
		offsetof(struct struct2, attr4),
		offsetof(struct struct3, attr4));
	printf (" attr5: %2zu %2zu %2zu\n",
		offsetof(struct struct1, attr5),
		offsetof(struct struct2, attr5),
		offsetof(struct struct3, attr5));
	printf (" attr6: %2zu %2zu %2zu\n",
		offsetof(struct struct1, attr6),
		offsetof(struct struct2, attr6),
		offsetof(struct struct3, attr6));

	return 0;
}
