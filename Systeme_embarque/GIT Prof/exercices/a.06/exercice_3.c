/**
 * Programmation C: Fonctions
 * solution de l'exercice 2
 */

#include <stdio.h>
#include <stdint.h>

/**
 * addition
 * @param a 1er paramètre
 * @param b 2eme paramètre
 * @result resultat de l'addition a+b
*/
float add (int32_t a, int32_t b) { return (float)a+(float)b; }

/**
 * sustraction
 * @param a 1er paramètre
 * @param b 2eme paramètre
 * @result resultat de la soustraction a-b
*/
float sub (int32_t a, int32_t b) { return (float)a-(float)b; }

/**
 * multiplication
 * @param a 1er paramètre
 * @param b 2eme paramètre
 * @result resultat de la multiplicaton a*b
*/
float mul (int32_t a, int32_t b) { return (float)a*(float)b; }

/**
 * division
 * @param a 1er paramètre
 * @param b 2eme paramètre
 * @result resultat de la division a/b
*/
float div (int32_t a, int32_t b) { return (float)a/(float)b; }

/*
 * programme principal
*/
int main(){

float   result;
int32_t a, b;

// addition
        a = 23;
        b = 19;
        result = add (a, b);
        printf("add : (%d) + (%d) = %e\n",a,b,result);
        
// soustraction        
        a = 10652;
        b = 26785;
        result = sub (a, b);
        printf("sub : (%d) - (%d) = %e\n",a,b,result);
        
// multiplication
        a = 4653;
        b = 3876;
        result = mul (a, b);
        printf("mul : (%d) * (%d) = %e\n",a,b,result);
        
// division
        a = 987;
        b = 1987;
        result = div (a, b);
        printf("div : (%d) / (%d) = %e\n",a,b,result);


        return 0;
}    

