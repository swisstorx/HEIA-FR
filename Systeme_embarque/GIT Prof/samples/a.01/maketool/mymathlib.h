#pragma once
#ifndef MYMATHLIB_H
#define MYMATHLIB_H
/**
 * A very simple library with mathematical functions
 */


 /**
 * The Fibonacci numbers form a sequence of integers, mathematically defined by
 *   F(0)=0; F(1)=1; F(n) = F(n - 1) + F(n - 2) for n > 1.
 *
 * This results in the following sequence of numbers:
 *	0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, ...
 * so that each new number is the sum of the previous two, after seeding
 * the sequence with the starting pair 0, 1.
 *
 * @param n value for which the Fibonacci number should be computed
 * @return Fibonacci number
 */
extern unsigned long fibonacci(unsigned long n);


/**
 * factorial: calcule la factorielle de la valeur n
 * @param n valeur pour laquelle la factorielle doit être calculée
 */
extern unsigned long factorial (unsigned long n);


#endif

