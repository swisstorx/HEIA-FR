/**
 * Programmation C: Design OO
 * solution de l'exercice 2
 */
#include <stdio.h>
#include <stddef.h>

#include "figure.h"
#include "trapeze.h"


int trapeze_draw (struct c_figure *oref)
{
	printf("trapeze(%p): draw\n", (void*)container_of (oref, struct c_trapeze, m_base));
	return 0;
}


int trapeze_move (struct c_figure *oref, int x_axis, int y_axis)
{
	printf("trapeze(%p): move x_axis:%d, y_axis:%d\n", (void*)container_of (oref, struct c_trapeze, m_base), x_axis, y_axis);
	return 0;
}

int trapeze_resize (struct c_figure *oref, int x_percent, int y_percent)
{
	printf("trapeze(%p): resize x_percent:%d, y_percent:%d\n", (void*)container_of (oref, struct c_trapeze, m_base), x_percent, y_percent);
	return 0;
}

int trapeze_rotate (struct c_figure *oref, int angle)
{
	printf("trapeze(%p): rotate angle:%d\n", (void*)container_of (oref, struct c_trapeze, m_base), angle);
	return 0;
}

int trapeze_erase (struct c_figure *oref)
{
	printf("trapeze(%p): erase\n", (void*)container_of (oref, struct c_trapeze, m_base));
	return 0;
}


int trapeze_show (struct c_figure *oref)
{
	struct c_trapeze* trapeze = container_of (oref, struct c_trapeze, m_base);
	printf("trapeze(%p): show :: ", (void*)trapeze);
	printf("p1:x:%d, p1:y:%d :: ",   trapeze->m_p1_origin.x_axis, trapeze->m_p1_origin.y_axis);
	printf("p2:x:%d, p2:y:%d :: ",   trapeze->m_p2_origin.x_axis, trapeze->m_p2_origin.y_axis);
	printf("p3:x:%d, p3:y:%d :: ",   trapeze->m_p3_origin.x_axis, trapeze->m_p3_origin.y_axis);
	printf("p4:x:%d, p4:y:%d\n", trapeze->m_p4_origin.x_axis, trapeze->m_p4_origin.y_axis);
	return 0;
}


struct c_figure* trapeze_init (struct c_trapeze *trapeze, 
                             int p1_x_axis, int p1_y_axis,
                             int p2_x_axis, int p2_y_axis,
                             int p3_x_axis, int p3_y_axis,
                             int p4_x_axis, int p4_y_axis)

{
    figure_init (&trapeze->m_base);

    trapeze->m_base.m_draw   = trapeze_draw;
    trapeze->m_base.m_move   = trapeze_move;
    trapeze->m_base.m_resize = trapeze_resize;
    trapeze->m_base.m_rotate = trapeze_rotate;
    trapeze->m_base.m_erase  = trapeze_erase;
    trapeze->m_base.m_show   = trapeze_show;

    trapeze->m_p1_origin.x_axis = p1_x_axis;
    trapeze->m_p1_origin.y_axis = p1_y_axis;
    trapeze->m_p2_origin.x_axis = p2_x_axis;
    trapeze->m_p2_origin.y_axis = p2_y_axis;
    trapeze->m_p3_origin.x_axis = p3_x_axis;
    trapeze->m_p3_origin.y_axis = p3_y_axis;
    trapeze->m_p4_origin.x_axis = p4_x_axis;
    trapeze->m_p4_origin.y_axis = p4_y_axis;

    return &trapeze->m_base;
}

