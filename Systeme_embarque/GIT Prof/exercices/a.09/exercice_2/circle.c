/**
 * Programmation C: Design OO
 * solution de l'exercice 2
 */
#include <stdio.h>

#include "figure.h"
#include "circle.h"


int circle_draw (struct c_figure *oref)
{
	printf("circle(%p): draw\n", (void*)container_of (oref, struct c_circle, m_base));
	return 0;
}


int circle_move (struct c_figure *oref, int x_axis, int y_axis)
{
	printf("circle(%p): move x_axis:%d, y_axis:%d\n", (void*)container_of (oref, struct c_circle, m_base), x_axis, y_axis);
	return 0;
}

int circle_resize (struct c_figure *oref, int x_percent, int y_percent)
{
	printf("circle(%p): resize x_percent:%d, y_percent:%d\n", (void*)container_of (oref, struct c_circle, m_base), x_percent, y_percent);
	return 0;
}

int circle_rotate (struct c_figure *oref, int angle)
{
	printf("circle(%p): rotate angle:%d\n", (void*)container_of (oref, struct c_circle, m_base), angle);
	return 0;
}

int circle_erase (struct c_figure *oref)
{
	printf("circle(%p): erase\n", (void*)container_of (oref, struct c_circle, m_base));
	return 0;
}


int circle_show (struct c_figure *oref)
{
	struct c_circle* circle = container_of (oref, struct c_circle, m_base);
	printf("circle(%p): show :: ", (void*)circle);
	printf("x_axis:%d, y_axis:%d, radius:%d\n", circle->m_origin.x_axis, circle->m_origin.y_axis, circle->m_radius);
	return 0;
}


struct c_figure* circle_init (struct c_circle *circle, int x_axis, int y_axis, int radius)
{
	figure_init (&circle->m_base);

	circle->m_base.m_draw   = circle_draw;
	circle->m_base.m_move   = circle_move;
	circle->m_base.m_resize = circle_resize;
	circle->m_base.m_rotate = circle_rotate;
	circle->m_base.m_erase  = circle_erase;
	circle->m_base.m_show   = circle_show;

	circle->m_origin.x_axis = x_axis;
	circle->m_origin.y_axis = y_axis;
	circle->m_radius = radius;

	return &circle->m_base;
}

