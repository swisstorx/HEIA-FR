/**
 * C-Programming - Pointers
 * solution of exercice #7
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


struct str {
	uint16_t val;
	struct str *next;
};

union exemple {
	uint32_t word;
	uint16_t hword;
	uint8_t byte;
	struct str elem;
	char mem[0x10];
} u;


int main()
{
	printf ("C-Programming - Pointers: solution of exercice #7\n");

	for (int i=0; i< 16; i++) u.mem[i] = i+1;
	printf ("word =%x\n", u.word);
	printf ("hword=%hx\n", u.hword);
	printf ("byte=%hhx\n", u.byte);
	printf ("ele.val=%hx\n", u.elem.val);
	printf ("ele.next=%p\n", u.elem.next);

	return 0;
}