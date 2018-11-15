#include <stdio.h>

struct rect{
    char instance[99];
    unsigned int heigth;
    unsigned int deep;
};

#define print(x) printf ("Voici le %s long de %d centimetres et  %d cm de long\n",x.instance,x.heigth,x.deep);

void main(){

    struct rect rectongle={
        .instance="Rectangle 1 ",
        .heigth =12,
        .deep =10,
    };

    struct rect rectongle2={"Rectangle 2 ",10289,12873,};
    print(rectongle);
    print(rectongle2);
}