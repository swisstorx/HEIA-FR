#include <stdio.h>
#include <unistd.h>


typedef void (*funptr)(char);

void ft_putchar(char c){
    write(1,&c,1);
    return;
}

int main(){
    funptr f;
    f=&ft_putchar;
    f('X');
    printf("\n");
}
