/**
 * Programmation C: Structures complexes
 * solution de l'exercice 3
 */

#include "nombre.h"
#include "opp.h"

/** 
 * realise l'addition de a et de b et le sauve dans c
 */
struct complex addi(const struct complex *a, const struct complex *b) 
{
	struct complex c = {
		.real = real_part(a) + real_part(b),
		.imag = imag_part(a) + imag_part(b),
	};
	return c;
}

/**
 * realise la soustraction de a et de b et le sauve dans c
 */
struct complex subs(const struct complex *a, const struct complex *b) 
{
	struct complex c = {
		.real = real_part(a) - real_part(b),
		.imag = imag_part(a) - imag_part(b),
	};
	return c;
}


