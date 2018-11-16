/**
 * Programmation C: Structures complexes
 * solution de l'exercice 1
 */
#include <stdio.h>


struct personne
{
	char classe;
	unsigned short ident;
	unsigned short age;
};

#define print(x) printf (#x ": classe=%c, ident=%d, age=%d\n", x.classe, x.ident, x.age);

int main()
{
	struct personne pers_a = {
		.classe = 'A',
		.ident = 12345,
		.age = 45,
	};

	struct personne pers_d = {'D', 987, 67};
	
	print (pers_a);
	print (pers_d);

	return 0;
}
