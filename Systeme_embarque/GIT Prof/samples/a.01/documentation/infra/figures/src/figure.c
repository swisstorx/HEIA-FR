#include <stdio.h>

#include "figure.h"

static int figure_draw (struct figure *self)
{
    printf("figure(%p): draw\n", self);
    return -1;
}


static int figure_move (struct figure *self, int x_axis, int y_axis)
{
    printf("figure(%p): move x_axis:%d, y_axis:%d\n", self, x_axis, y_axis);
    return -1;
}

static int figure_resize (struct figure *self, int x_percent, int y_percent)
{
    printf("figure(%p): resize x_percent:%d, y_percent:%d\n", self, x_percent, y_percent);
    return -1;
}

static int figure_rotate (struct figure *self, int angle)
{
    printf("figure(%p): rotate angle:%d\n", self, angle);
    return -1;
}

static int figure_erase (struct figure *self)
{
    printf("figure(%p): erase\n", self);
    return -1;
}

static int figure_show (struct figure *self)
{
    printf("figure(%p): show\n", self);
    return -1;
}


struct figure* figure_init (struct figure *fig)
{
    fig->draw   = figure_draw;
    fig->move   = figure_move;
    fig->resize = figure_resize;
    fig->rotate = figure_rotate;
    fig->erase  = figure_erase;
    fig->show   = figure_show;

    return fig;
}


