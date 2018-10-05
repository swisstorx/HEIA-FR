/**
 * A very simple library with mathematical functions
 */

#include "mymathlib.h"


unsigned long fibonacci(unsigned long n)
{
  if (n <= 1) return n;
  return fibonacci(n-1)+fibonacci(n-2);
}


unsigned long factorial (unsigned long n)
{
    if (n > 0) return n * factorial(n-1);
    return 1;
}


