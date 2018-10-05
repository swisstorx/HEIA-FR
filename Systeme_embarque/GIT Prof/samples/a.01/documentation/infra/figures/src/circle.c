#include <stdio.h>
#include <stddef.h>

#include "figure.h"
#include "circle.h"


#define container_of(ptr, type, member)\
((type*) ((char*)(ptr) - offsetof(type, member)))


static int circle_draw (struct figure *self)
{
    printf("circle(%p): draw\n", container_of (self, struct circle, base));
    return 0;
}


static int circle_move (struct figure *self, int x_axis, int y_axis)
{
    printf("circle(%p): move x_axis:%d, y_axis:%d\n", container_of (self, struct circle, base), x_axis, y_axis);
    return 0;
}

static int circle_resize (struct figure *self, int x_percent, int y_percent)
{
    printf("circle(%p): resize x_percent:%d, y_percent:%d\n", container_of (self, struct circle, base), x_percent, y_percent);
    return 0;
}

static int circle_rotate (struct figure *self, int angle)
{
    printf("circle(%p): rotate angle:%d\n", container_of (self, struct circle, base), angle);
    return 0;
}

static int circle_erase (struct figure *self)
{
    printf("circle(%p): erase\n", container_of (self, struct circle, base));
    return 0;
}


static int circle_show (struct figure *self)
{
    struct circle* circle = container_of (self, struct circle, base);
    printf("circle(%p): show :: ", circle);
    printf("x_axis:%d, y_axis:%d, radius:%d\n", circle->origin.x_axis, circle->origin.y_axis, circle->radius);
    return 0;
}


struct figure* circle_init (struct circle *circle, int x_axis, int y_axis, int radius)
{
    figure_init (&circle->base);

    circle->base.draw   = circle_draw;
    circle->base.move   = circle_move;
    circle->base.resize = circle_resize;
    circle->base.rotate = circle_rotate;
    circle->base.erase  = circle_erase;
    circle->base.show   = circle_show;

    circle->origin.x_axis = x_axis;
    circle->origin.y_axis = y_axis;
    circle->radius = radius;

    return &circle->base;
}

