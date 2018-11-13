#include <stdio.h>

int f(int a, int b){
    printf("foo\n");
    return a+b;
}

void main(int argc, char const *argv[])
{
    int x; 
    int(*p)(int,int);
    p=&f;
}
