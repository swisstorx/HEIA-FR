#pragma once
#ifndef TRIANGLE_H
#define TRIANGLE_H
/**
 * Programmation C: Design OO
 * solution de l'exercice 2
 */

#include "figure.h"

struct c_triangle
{
    struct point m_p1_origin;
    struct point m_p2_origin;
    struct point m_p3_origin;
    struct c_figure m_base;
};

extern struct c_figure* triangle_init (struct c_triangle *triangle, 
                                       int p1_x_axis, int p1_y_axis,
                                       int p2_x_axis, int p2_y_axis,
                                       int p3_x_axis, int p3_y_axis);

extern int triangle_draw (struct c_figure *oref);
extern int triangle_move (struct c_figure *oref, int x_axis, int y_axis);
extern int triangle_resize (struct c_figure *oref, int x_percent, int y_percent);
extern int triangle_rotate (struct c_figure *oref, int angle);
extern int triangle_erase (struct c_figure *oref);
extern int triangle_show (struct c_figure *oref);

#endif
