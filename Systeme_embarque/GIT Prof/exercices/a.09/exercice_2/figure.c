/**
 * Programmation C: Design OO
 * solution de l'exercice 2
 */

#include <stdio.h>
#include "figure.h"

int figure_draw (struct c_figure *oref)
{
	printf("figure(%p): draw\n", (void*)oref);
	return -1;
}


int figure_move (struct c_figure *oref, int x_axis, int y_axis)
{
	printf("figure(%p): move x_axis:%d, y_axis:%d\n", (void*)oref, x_axis, y_axis);
	return -1;
}

int figure_resize (struct c_figure *oref, int x_percent, int y_percent)
{
	printf("figure(%p): resize x_percent:%d, y_percent:%d\n", (void*)oref, x_percent, y_percent);
	return -1;
}

int figure_rotate (struct c_figure *oref, int angle)
{
	printf("figure(%p): rotate angle:%d\n", (void*)oref, angle);
	return -1;
}

int figure_erase (struct c_figure *oref)
{
	printf("figure(%p): erase\n", (void*)oref);
	return -1;
}

int figure_show (struct c_figure *oref)
{
	printf("figure(%p): show\n", (void*)oref);
	return -1;
}


struct c_figure* figure_init (struct c_figure *fig)
{
	fig->m_draw   = figure_draw;
	fig->m_move   = figure_move;
	fig->m_resize = figure_resize;
	fig->m_rotate = figure_rotate;
	fig->m_erase  = figure_erase;
	fig->m_show   = figure_show;
	return fig;
}

