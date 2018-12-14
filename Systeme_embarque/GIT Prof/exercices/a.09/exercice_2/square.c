/**
 * Programmation C: Design OO
 * solution de l'exercice 2
 */
#include <stdio.h>
#include <stddef.h>

#include "figure.h"
#include "square.h"

int square_draw (struct c_figure *oref)
{
	printf("square(%p): draw\n", (void*)container_of (oref, struct c_square, m_base));
	return 0;
}


int square_move (struct c_figure *oref, int x_axis, int y_axis)
{
	printf("square(%p): move x_axis:%d, y_axis:%d\n", (void*)container_of (oref, struct c_square, m_base), x_axis, y_axis);
	return 0;
}

int square_resize (struct c_figure *oref, int x_percent, int y_percent)
{
	printf("square(%p): resize x_percent:%d, y_percent:%d\n", (void*)container_of (oref, struct c_square, m_base), x_percent, y_percent);
	return 0;
}

int square_rotate (struct c_figure *oref, int angle)
{
	printf("square(%p): rotate angle:%d\n", (void*)container_of (oref, struct c_square, m_base), angle);
	return 0;
}

int square_erase (struct c_figure *oref)
{
	printf("square(%p): erase\n", (void*)container_of (oref, struct c_square, m_base));
	return 0;
}


int square_show (struct c_figure *oref)
{
	struct c_square* square = container_of (oref, struct c_square, m_base);
	printf("square(%p): show :: ", (void*)square);
	printf("x_axis:%d, y_axis:%d, length:%d\n", square->m_x_axis, square->m_y_axis, square->m_length);
	return 0;
}


struct c_figure* square_init (struct c_square *square, int x_axis, int y_axis, int length)
{
	figure_init (&square->m_base);

	square->m_base.m_draw   = square_draw;
	square->m_base.m_move   = square_move;
	square->m_base.m_resize = square_resize;
	square->m_base.m_rotate = square_rotate;
	square->m_base.m_erase  = square_erase;
	square->m_base.m_show   = square_show;

	square->m_x_axis = x_axis;
	square->m_y_axis = y_axis;
	square->m_length = length;

	return &square->m_base;
}

