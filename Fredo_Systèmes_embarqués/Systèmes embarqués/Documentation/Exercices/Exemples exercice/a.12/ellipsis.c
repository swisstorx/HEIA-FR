#include <stdio.h>
#include <stdarg.h>

void printargs (int argc, ...)
{
	va_list ap;
	va_start (ap, argc);
	while (argc-- > 0) {
		int i = va_arg (ap, int);
		printf ("%d ", i);
	}
	va_end(ap);
	printf ("\n");
}


int main()
{
	printargs (4, 10, 45, 78, -1);
	return 0;
}
