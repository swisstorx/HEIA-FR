/**
 * A second simple exemple of a C program using a own made library
 */
#include <stdio.h>
#include <stdlib.h>

#include "mymathlib.h"

/**
 * Main program computing the Fibonacci numbers and the
 * factorial for a number specified at the command line.
 */
int main (int argc, char** argv)
{
    unsigned long n = 0;
    if (argc == 2) {
        n = abs(atoi(argv[1]));
    }

    printf("For n=%lu\n", n);
    printf("  the Fibonacci number is: %lu\n", fibonacci(n));
    printf("  the factorial        is: %lu\n", factorial(n));

    return 0;
}
