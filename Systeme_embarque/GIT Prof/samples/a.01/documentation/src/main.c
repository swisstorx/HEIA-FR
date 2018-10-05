#include <stdio.h>
#include <stdlib.h>

#include "figure.h"
#include "square.h"
#include "trapeze.h"
#include "triangle.h"
#include "circle.h"
#include "group.h"

#include "mymathlib.h"


int main (int argc, char** argv)
{
    int i;
    struct figure* fig[6];
    struct figure figure;
    struct square square;
    struct trapeze trapeze;
    struct circle circle;
    struct triangle triangle;
    struct group group;

    fig[0] = figure_init (&figure);
    fig[1] = square_init (&square, 10,20, 10);
    fig[2] = trapeze_init (&trapeze, 10,20, 30,40, 50,60, 70,80);
    fig[3] = circle_init (&circle, 80,90, 10);
    fig[4] = triangle_init (&triangle, 10,20, 60,50, 30,40);
    fig[5] = group_init (&group);

    for (i=0; i<6; i++) {
        fig[i]->draw   (fig[i]);
        fig[i]->move   (fig[i], 10, 20);
        fig[i]->resize (fig[i], -10, 100);
        fig[i]->rotate (fig[i], -45);
        fig[i]->erase  (fig[i]);
        fig[i]->show   (fig[i]);
    }

    printf("\n\n");
    for (i=0; i<5; i++) {
        group.add (&group, fig[i]);
    }
    fig[5]->draw   (fig[5]);            printf ("\n");
    fig[5]->move   (fig[5], 10, 20);    printf ("\n");
    fig[5]->resize (fig[5], -10, 100);  printf ("\n");
    fig[5]->rotate (fig[5], -45);       printf ("\n");
    fig[5]->erase  (fig[5]);            printf ("\n");
    fig[5]->show   (fig[5]);            printf ("\n");

    printf("\n");
    for (i=0; i<5; i++) {
        group.remove (&group, fig[i]);
    }
    fig[5]->draw   (fig[5]);
    fig[5]->move   (fig[5], 10, 20);
    fig[5]->resize (fig[5], -10, 100);
    fig[5]->rotate (fig[5], -45);
    fig[5]->erase  (fig[5]);
    fig[5]->show   (fig[5]);


    printf("\n\n");
    unsigned long n = 0;
    if (argc == 2) {
        n = abs(atol(argv[1]));
    }

    printf("For n=%lu\n", n);
    printf("  the Fibonacci number is: %lu\n", fibonacci(n));
    printf("  the factorial        is: %lu\n", factorial(n));


    return 0;
}
