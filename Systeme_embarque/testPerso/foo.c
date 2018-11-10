#include <stdio.h>

void foo(void)
{
     printf("foo\nim pointed \n");
}

int main (void)
{
     void (*pointeurSurFonction)(void);         /*déclaration du pointeur*/
     pointeurSurFonction = &foo;                 /*Initialisation*/

     (*pointeurSurFonction)();                  /*Appel de la fonction*/

     return 0;
}
