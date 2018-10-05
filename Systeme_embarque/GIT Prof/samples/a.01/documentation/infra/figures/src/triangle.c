#include <stdio.h>
#include <stddef.h>

#include "figure.h"
#include "triangle.h"


#define container_of(ptr, type, member)\
((type*) ((char*)(ptr) - offsetof(type, member)))


static int triangle_draw (struct figure *self)
{
    printf("triangle(%p): draw\n", container_of (self, struct triangle, base));
    return 0;
}


static int triangle_move (struct figure *self, int x_axis, int y_axis)
{
    printf("triangle(%p): move x_axis:%d, y_axis:%d\n", container_of (self, struct triangle, base), x_axis, y_axis);
    return 0;
}

static int triangle_resize (struct figure *self, int x_percent, int y_percent)
{
    printf("triangle(%p): resize x_percent:%d, y_percent:%d\n", container_of (self, struct triangle, base), x_percent, y_percent);
    return 0;
}

static int triangle_rotate (struct figure *self, int angle)
{
    printf("triangle(%p): rotate angle:%d\n", container_of (self, struct triangle, base), angle);
    return 0;
}

static int triangle_erase (struct figure *self)
{
    printf("triangle(%p): erase\n", container_of (self, struct triangle, base));
    return 0;
}


static int triangle_show (struct figure *self)
{
    struct triangle* triangle = container_of (self, struct triangle, base);
    printf("triangle(%p): show :: ", triangle);
    printf("p1:x:%d, p1:y:%d",   triangle->p1_origin.x_axis, triangle->p1_origin.y_axis);
    printf("p2:x:%d, p2:y:%d",   triangle->p2_origin.x_axis, triangle->p2_origin.y_axis);
    printf("p3:x:%d, p3:y:%d\n", triangle->p3_origin.x_axis, triangle->p3_origin.y_axis);
    return 0;
}


struct figure* triangle_init (struct triangle *triangle,
                              int p1_x_axis, int p1_y_axis,
                              int p2_x_axis, int p2_y_axis,
                              int p3_x_axis, int p3_y_axis)
{
    figure_init (&triangle->base);

    triangle->base.draw   = triangle_draw;
    triangle->base.move   = triangle_move;
    triangle->base.resize = triangle_resize;
    triangle->base.rotate = triangle_rotate;
    triangle->base.erase  = triangle_erase;
    triangle->base.show   = triangle_show;

    triangle->p1_origin.x_axis = p1_x_axis;
    triangle->p1_origin.y_axis = p1_y_axis;
    triangle->p2_origin.x_axis = p2_x_axis;
    triangle->p2_origin.y_axis = p2_y_axis;
    triangle->p3_origin.x_axis = p3_x_axis;
    triangle->p3_origin.y_axis = p3_y_axis;

    return &triangle->base;
}

