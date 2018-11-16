/**
 * Programmation C: Structures complexes
 * solution de l'exercice 2
 */

#include <stdio.h>

struct message {
	unsigned char info[10];
	unsigned char parity;
};

/**
 * fonction de calcul de la parité
 * effectue le calcul de la parité verticale
 *
 * @param msg message
 * @return partité calculée sur le message
 */
unsigned char calc_parity (struct message msg)
{
	unsigned char parity=0;
	for (unsigned i=0; i<sizeof(msg.info); i++) {
		parity ^= msg.info[i];
	}
	return parity;
}

char* c2b (char c)
{
	static char binary[9] = {[8]=0,};
	for (int i=0; i<8; i++) binary[i] = ((c & (1<<i)) != 0) ? '1' : '0';
	return binary;
}

int main()
{
	struct message msg = {
		.info = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99},
	};
	msg.parity = calc_parity (msg);

	for (unsigned i=0; i<sizeof(msg.info); i++)
		printf ("msg.info[%d]=%s\n", i, c2b(msg.info[i]));
	printf ("msg.parity =%s\n", c2b(msg.parity));

	return 0;
}


