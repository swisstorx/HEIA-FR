#include <stdio.h>

static int fooInGlobal=1;

void foo(){
    static int fooInRemanent = 10;//variable rémanente
    fooInRemanent++;
    fooInGlobal++;
    printf("variable Globale =  %d\net variable rémanente %d\n ",fooInGlobal,fooInRemanent);
}

void main(){

    int nbItr = 10;
    while(nbItr>0){
        foo();
        nbItr--;
    }   
}
