/**
 * Programmation C: Structures complexes
 * solution de l'exercice 3
 */

#include "nombre.h"

long real_part(const struct complex *nbre)
{
	long real = nbre->real;
	if (nbre->real > REAL_MAX) real = REAL_MAX;
	else if (nbre->real < REAL_MIN) real = REAL_MIN;

	return real;
}


long imag_part(const struct complex *nbre)
{
	long imag = nbre->imag;
	if (nbre->imag > IMAG_MAX) imag = IMAG_MAX;
	else if (nbre->real < IMAG_MIN) imag = IMAG_MIN;

	return imag;
}

