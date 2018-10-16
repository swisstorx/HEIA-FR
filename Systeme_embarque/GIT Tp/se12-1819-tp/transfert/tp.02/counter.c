/*
 * counter.c
 *
 *  Created on: Oct 1, 2018
 *      Author: sven
 */

#include "seg7.h"
#include "wheel.h"

/*
j'avais pensé récupérer le compteur ici
*/

extern int counter =0;
int updateCounter(int a){
    if(a==1){
        counter  +=1;
        }else if(a==2){
            counter -=1;
        }else break;
    return counter;   
}