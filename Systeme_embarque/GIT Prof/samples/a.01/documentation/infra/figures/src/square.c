#include <stdio.h>
#include <stddef.h>

#include "figure.h"
#include "square.h"


#define container_of(ptr, type, member)\
((type*) ((char*)(ptr) - offsetof(type, member)))


static int square_draw (struct figure *self)
{
    printf("square(%p): draw\n", container_of (self, struct square, base));
    return 0;
}


static int square_move (struct figure *self, int x_axis, int y_axis)
{
    printf("square(%p): move x_axis:%d, y_axis:%d\n", container_of (self, struct square, base), x_axis, y_axis);
    return 0;
}

static int square_resize (struct figure *self, int x_percent, int y_percent)
{
    printf("square(%p): resize x_percent:%d, y_percent:%d\n", container_of (self, struct square, base), x_percent, y_percent);
    return 0;
}

static int square_rotate (struct figure *self, int angle)
{
    printf("square(%p): rotate angle:%d\n", container_of (self, struct square, base), angle);
    return 0;
}

static int square_erase (struct figure *self)
{
    printf("square(%p): erase\n", container_of (self, struct square, base));
    return 0;
}


static int square_show (struct figure *self)
{
    struct square* square = container_of (self, struct square, base);
    printf("square(%p): show :: ", square);
    printf("x_axis:%d, y_axis:%d, length:%d\n", square->origin.x_axis, square->origin.y_axis, square->length);
    return 0;
}


struct figure* square_init (struct square *square, int x_axis, int y_axis, int length)
{
    figure_init (&square->base);

    square->base.draw   = square_draw;
    square->base.move   = square_move;
    square->base.resize = square_resize;
    square->base.rotate = square_rotate;
    square->base.erase  = square_erase;
    square->base.show   = square_show;

    square->origin.x_axis = x_axis;
    square->origin.y_axis = y_axis;
    square->length = length;

    return &square->base;
}

