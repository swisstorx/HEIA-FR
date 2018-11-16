/**
 * simple example about operator # and ## 
 */
#include <stdio.h>

#define printd(x) printf (#x "=%d\n", x)
#define print2(a,b) printf (#a#b "=%s\n", a##b)
#define printa(x) printf (#x "=%s\n", x)

#define alpha "aaaa"
#define beta  "bbbb"
#define alphabeta alpha beta


int main ()
{
	int x=0;

	printd(10*11);
	printd(x*11);
	print2(alpha,beta);
	printa(alphabeta);

	return 0;
}
