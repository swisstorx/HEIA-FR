/* Interrupt handling
 * Exercice 4 : solution
 */

#include <stdlib.h>
#include <stdio.h>

#include "svc.h"

typedef int (*fnct_t)();

int fnct1_1() {return 0x11;}
int fnct1_2() {return 0x12;}
int fnct1_3() {return 0x13;}
int fnct1_4() {return 0x14;}
int fnct1_5() {return 0x15;}

int fnct5_1() {return 0x51;}
int fnct5_2() {return 0x52;}
int fnct5_3() {return 0x53;}
int fnct5_4() {return 0x54;}
int fnct5_5() {return 0x55;}

/* ------------------------------------------------------------------------- */

fnct_t table1[5] = {fnct1_1, fnct1_2, fnct1_3, fnct1_4, fnct1_5}; 
fnct_t table5[5] = {fnct5_1, fnct5_2, fnct5_3, fnct5_4, fnct5_5};

void* stack[20000];


static int svc_handler(int fnct, int table) {
	int status = 0;
	fnct_t* tab = table1;
	switch (table) {
		case 1: tab = table1;  break;
		case 5: tab = table5;  break;
		default: status = -1;
	}

	if (status == 0) {
		status = -1;
		if ((fnct >= 1) && (fnct <= 5)) {
			status = tab[fnct-1]();
		}
	}
	printf ("table:%d, function:%d, status:0x%x\n",
		table, fnct, status);
	return status;
}

/* ------------------------------------------------------------------------- */

int main () 
{
	printf ("Exercice sur les interruptions software (svc)\n"); 
	printf ("---------------------------------------------\n");

	svc_init(svc_handler, stack, sizeof(stack)); 

	int status = 0;
	while (1) {
		for (int i=1; i<=5; i++) status = svc_1_call (i); 
		for (int i=1; i<=5; i++) status = svc_5_call (i);
	}
	
	return status; 
}

