/**
 * C-Programming - Pointers
 * solution of exercice #7
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>


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

const char* i2s (char val, bool ok, char* s)
{
	strcpy (s, "x ");
	if (ok) sprintf (s, "%02hhx", val);
	return s;
}


int main()
{
	printf ("C-Programming - Pointers: solution of exercice #7\n");

	union exemple u1 = {.word = 1536, };
	union exemple u2 = {.hword = -3, };
	union exemple u3 = {.byte = 96, };
	union exemple u4 = {.elem = {.val = 127, .next = &u.elem}, };
	printf ("u1.word=%08x (%zu), u2.hword=%04x (%zu), u3.byte=%02hhx (%zu), u4.val=%04x (%zu), u4.next=%p (%zu)\n",
		u1.word, sizeof (uint32_t), u2.hword, sizeof(uint16_t), u3.byte, sizeof(uint16_t),
		u4.elem.val, sizeof(uint16_t), u4.elem.next, sizeof(struct str*));
	printf ("address  a)  b)  c)  d)  e)\n");
	for (size_t i=0; i<0x10; i++) {
		long addr=0x2000;
		char su1[4];
		char su2[4];
		char su3[4];
		char su41[4];
		char su42[4];
		printf ("0x%4lx   %s  %s  %s  %s  %s\n",
			addr+i, i2s(u1.mem[i], i<sizeof(uint32_t), su1),
				i2s(u2.mem[i], i<sizeof(uint16_t), su2),
				i2s(u3.mem[i], i<sizeof(uint8_t), su3),
				i2s(u4.mem[i], (i >= offsetof(struct str, val)) &&
					       ((i-offsetof(struct str, val))<sizeof(u4.elem.val)), su41),
				i2s(u4.mem[i], (i >= offsetof(struct str, next)) &&
					       ((i-offsetof(struct str, next))<sizeof(u4.elem.next)), su42));
	}

	return 0;
}
