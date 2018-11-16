/**
 * A simple exemple of a C program
 */
#include <stdio.h>
#include <stdlib.h>
    
/**
 * The Fibonacci numbers form a sequence of integers, mathematically defined by 
 *   F(0)=0; F(1)=1; F(n) = F(n - 1) + F(n - 2) for n > 1.
 *  
 * This results in the following sequence of numbers: 0, 1, 1, 2, 3, 5, 8, 13, 
 *    21, 34, 55, 89, 144, 233, 377, 610, 987, ...
 * so that each new number is the sum of the previous two, after seeding the 
 * sequence with the starting pair 0, 1.
 *  
 * @param n value for which the Fibonacci number should be computed
 * @return Fibonacci number 
 */
long fibonacci(long n)
{
  if (n <= 1) return n;
  return fibonacci(n-1)+fibonacci(n-2);
}


/**
 * Main program computing the Fibonacci numbers for a given sequence starting 
 * from 0 to a number specified at the command line. 
 */
int main (int argc, char** argv)
{
    long n = 0;
    long i = 0;

    if (argc == 2) {
        n = atol(argv[1]);
    }

    printf("The first %ld Fibonacci numbers are:\n", n);
    printf("%s, %d, %s, %s\n", __FILE__, __LINE__, __DATE__, __TIME__);

    for (i=0; i<=n; i++) {
        printf("%ld, ", fibonacci(i));
    }
    printf("\n");

    return 0;
}
