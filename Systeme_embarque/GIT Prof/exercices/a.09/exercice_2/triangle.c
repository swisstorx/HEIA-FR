/**
 * Programmation C: Design OO
 * solution de l'exercice 2
 */
#include <stdio.h>
#include <stddef.h>

#include "figure.h"
#include "triangle.h"


int triangle_draw (struct c_figure *oref)
{
	printf("triangle(%p): draw\n", (void*)container_of (oref, struct c_triangle, m_base));
	return 0;
}


int triangle_move (struct c_figure *oref, int x_axis, int y_axis)
{
	printf("triangle(%p): move x_axis:%d, y_axis:%d\n", (void*)container_of (oref, struct c_triangle, m_base), x_axis, y_axis);
	return 0;
}

int triangle_resize (struct c_figure *oref, int x_percent, int y_percent)
{
	printf("triangle(%p): resize x_percent:%d, y_percent:%d\n", (void*)container_of (oref, struct c_triangle, m_base), x_percent, y_percent);
	return 0;
}

int triangle_rotate (struct c_figure *oref, int angle)
{
	printf("triangle(%p): rotate angle:%d\n", (void*)container_of (oref, struct c_triangle, m_base), angle);
	return 0;
}

int triangle_erase (struct c_figure *oref)
{
	printf("triangle(%p): erase\n", (void*)container_of (oref, struct c_triangle, m_base));
	return 0;
}


int triangle_show (struct c_figure *oref)
{
	struct c_triangle* triangle = container_of (oref, struct c_triangle, m_base);
	printf("triangle(%p): show :: ", (void*)triangle);
	printf("p1:x:%d, p1:y:%d :: ",   triangle->m_p1_origin.x_axis, triangle->m_p1_origin.y_axis);
	printf("p2:x:%d, p2:y:%d :: ",   triangle->m_p2_origin.x_axis, triangle->m_p2_origin.y_axis);
	printf("p3:x:%d, p3:y:%d\n", triangle->m_p3_origin.x_axis, triangle->m_p3_origin.y_axis);
	return 0;
}


struct c_figure* triangle_init (struct c_triangle *triangle, 
                                int p1_x_axis, int p1_y_axis,
                                int p2_x_axis, int p2_y_axis,
                                int p3_x_axis, int p3_y_axis)
{
	figure_init (&triangle->m_base);

	triangle->m_base.m_draw   = triangle_draw;
	triangle->m_base.m_move   = triangle_move;
	triangle->m_base.m_resize = triangle_resize;
	triangle->m_base.m_rotate = triangle_rotate;
	triangle->m_base.m_erase  = triangle_erase;
	triangle->m_base.m_show   = triangle_show;

	triangle->m_p1_origin.x_axis = p1_x_axis;
	triangle->m_p1_origin.y_axis = p1_y_axis;
	triangle->m_p2_origin.x_axis = p2_x_axis;
	triangle->m_p2_origin.y_axis = p2_y_axis;
	triangle->m_p3_origin.x_axis = p3_x_axis;
	triangle->m_p3_origin.y_axis = p3_y_axis;

	return &triangle->m_base;
}

