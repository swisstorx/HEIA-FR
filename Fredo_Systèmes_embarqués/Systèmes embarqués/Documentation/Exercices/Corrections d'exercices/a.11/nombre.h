#pragma once
#ifndef nombre_h
#define nombre_h
/**
 * Programmation C: Structures complexes
 * solution de l'exercice 3
 */

#define REAL_MAX 200000
#define REAL_MIN -200000

#define IMAG_MAX 200000
#define IMAG_MIN -200000

struct complex {
	long real;
	long imag;
};

extern long real_part(const struct complex *nbre);
extern long imag_part(const struct complex *nbre);

#endif
