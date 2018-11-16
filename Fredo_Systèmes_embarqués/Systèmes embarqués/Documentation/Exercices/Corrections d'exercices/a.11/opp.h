#pragma once
#ifndef opp_h
#define opp_h
/**
 * Programmation C: Structures complexes
 * solution de l'exercice 3
 */

#include "nombre.h"

/** 
 * realise l'addition de a et de b et le sauve dans c
 */
extern struct complex addi(const struct complex *a, const struct complex *b);

/**
 * realise la soustraction de a et de b et le sauve dans c
 */
extern struct complex subs(const struct complex *a, const struct complex *b) ;

#endif
