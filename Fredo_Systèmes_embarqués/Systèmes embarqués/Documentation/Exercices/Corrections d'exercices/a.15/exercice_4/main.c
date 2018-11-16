/* Interfacing C with assembleur
 * Exercice 4 : solution
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "callback.h"

/**
 * small macro to test the result of an operation and to display
 * error message on the shell in case of failure (valid == false)
 */
#define SUCCESSFULL(valid,...)\
do {\
	successfull &= (valid);\
	if (!(valid)) printf (__VA_ARGS__);\
} while (0)

/* ------------------------------------------------------------------------- */

static int fnct1 (void* param, int arg1, int arg2, void* arg3)
{
	printf("callback: fnct1: param=%p, arg1=%d, arg2=%d, arg3=%p\n", 
		   param, arg1, arg2, arg3);
	*(int*)arg3 = 100+(int)param + arg1 + arg2;
	return 0;
}


/* ------------------------------------------------------------------------- */

static int fnct2 (void* param, int arg1, int arg2, void* arg3)
{
	printf("callback: fnct2: param=%p, arg1=%d, arg2=%d, arg3=%p\n", 
		   param, arg1, arg2, arg3);
	*(int*)arg3 = 200+(int)param + arg1 + arg2;
	return 0;
}


/* ------------------------------------------------------------------------- */


int main ()
{
	int status = 0;
	bool successfull = true;

	printf ("Programmation C: Pointeurs de fonction: Interfacing assembler <-> C (exercice #4)\n");
	
	/* initialisation */
	callback_init();

	/* installation of the call-back methods */
	for (int i = 0; i < MAX_NB_OF_FUNCTIONS; i++) {
		status = callback_attach (i, ((i % 2) == 0) ? fnct1 : fnct2, (void*)i);
		SUCCESSFULL (status==0, "ERROR: could not attach the function at index=%d\n", i);
	}
	status = callback_attach (0, fnct1, 0);
	SUCCESSFULL (status!=0, "ERROR: callback_attach: already attached element not well checked\n");
	status = callback_attach (MAX_NB_OF_FUNCTIONS, fnct1, 0);
	SUCCESSFULL (status!=0, "ERROR: callback_attach: max number of elements not well checked\n");

	/* call⁻back operations */
	for (int i = 0; i < MAX_NB_OF_FUNCTIONS; i++) {
		int res=0;
		status = callback_call (i, 10, 20, &res);
		SUCCESSFULL (status==0, "ERROR: callback_call: error while calling the function\n");
		int expected = i + 10 + 20 + (((i % 2) == 0) ? 100 : 200);
		SUCCESSFULL (expected == res, "ERROR: callback_call: wrong argument's passing\n");
	}
	status = callback_call (MAX_NB_OF_FUNCTIONS, 0, 0, 0);
	SUCCESSFULL (status!=0, "ERROR: callback_call: max number of elements not well checked\n");

	/* removal of the call-back methods */
	for (int i = 0; i < MAX_NB_OF_FUNCTIONS; i++) {
		callback_detach (i);
	}
	status = callback_call (0, 0, 0, 0);
	SUCCESSFULL (status!=0, "ERROR: callback_call: unattached element not well tested\n");

	/* display results on the shell */
	printf ("Call-back: tests %s\n", successfull ? "successfully passed." : "passed with errors!");

	while (1);

	return 0;
}
