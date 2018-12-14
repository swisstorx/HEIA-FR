#pragma once
#ifndef TRAPEZE_H
#define TRAPEZE_H
/**
 * Programmation C: Design OO
 * solution de l'exercice 2
 */

#include "figure.h"

struct c_trapeze {
    struct point m_p1_origin;
    struct point m_p2_origin;
    struct point m_p3_origin;
    struct point m_p4_origin;
    struct c_figure m_base;
};

extern struct c_figure* trapeze_init (struct c_trapeze *trapeze, 
                                      int p1_x_axis, int p1_y_axis,
                                      int p2_x_axis, int p2_y_axis,
                                      int p3_x_axis, int p3_y_axis,
                                      int p4_x_axis, int p4_y_axis);

extern int trapeze_draw (struct c_figure *oref);
extern int trapeze_move (struct c_figure *oref, int x_axis, int y_axis);
extern int trapeze_resize (struct c_figure *oref, int x_percent, int y_percent);
extern int trapeze_rotate (struct c_figure *oref, int angle);
extern int trapeze_erase (struct c_figure *oref);
extern int trapeze_show (struct c_figure *oref);

#endif
