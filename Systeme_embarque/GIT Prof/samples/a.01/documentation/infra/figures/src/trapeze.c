#include <stdio.h>
#include <stddef.h>

#include "figure.h"
#include "trapeze.h"


#define container_of(ptr, type, member)\
((type*) ((char*)(ptr) - offsetof(type, member)))


static int trapeze_draw (struct figure *self)
{
    printf("trapeze(%p): draw\n", container_of (self, struct trapeze, base));
    return 0;
}


static int trapeze_move (struct figure *self, int x_axis, int y_axis)
{
    printf("trapeze(%p): move x_axis:%d, y_axis:%d\n", container_of (self, struct trapeze, base), x_axis, y_axis);
    return 0;
}

static int trapeze_resize (struct figure *self, int x_percent, int y_percent)
{
    printf("trapeze(%p): resize x_percent:%d, y_percent:%d\n", container_of (self, struct trapeze, base), x_percent, y_percent);
    return 0;
}

static int trapeze_rotate (struct figure *self, int angle)
{
    printf("trapeze(%p): rotate angle:%d\n", container_of (self, struct trapeze, base), angle);
    return 0;
}

static int trapeze_erase (struct figure *self)
{
    printf("trapeze(%p): erase\n", container_of (self, struct trapeze, base));
    return 0;
}


static int trapeze_show (struct figure *self)
{
    struct trapeze* trapeze = container_of (self, struct trapeze, base);
    printf("trapeze(%p): show :: ", trapeze);
    printf("p1:x:%d, p1:y:%d",   trapeze->p1_origin.x_axis, trapeze->p1_origin.y_axis);
    printf("p2:x:%d, p2:y:%d",   trapeze->p2_origin.x_axis, trapeze->p2_origin.y_axis);
    printf("p3:x:%d, p3:y:%d",   trapeze->p3_origin.x_axis, trapeze->p3_origin.y_axis);
    printf("p4:x:%d, p4:y:%d\n", trapeze->p4_origin.x_axis, trapeze->p4_origin.y_axis);
    return 0;
}


struct figure* trapeze_init (struct trapeze *trapeze,
                             int p1_x_axis, int p1_y_axis,
                             int p2_x_axis, int p2_y_axis,
                             int p3_x_axis, int p3_y_axis,
                             int p4_x_axis, int p4_y_axis)

{
    figure_init (&trapeze->base);

    trapeze->base.draw   = trapeze_draw;
    trapeze->base.move   = trapeze_move;
    trapeze->base.resize = trapeze_resize;
    trapeze->base.rotate = trapeze_rotate;
    trapeze->base.erase  = trapeze_erase;
    trapeze->base.show   = trapeze_show;

    trapeze->p1_origin.x_axis = p1_x_axis;
    trapeze->p1_origin.y_axis = p1_y_axis;
    trapeze->p2_origin.x_axis = p2_x_axis;
    trapeze->p2_origin.y_axis = p2_y_axis;
    trapeze->p3_origin.x_axis = p3_x_axis;
    trapeze->p3_origin.y_axis = p3_y_axis;
    trapeze->p4_origin.x_axis = p4_x_axis;
    trapeze->p4_origin.y_axis = p4_y_axis;

    return &trapeze->base;
}

