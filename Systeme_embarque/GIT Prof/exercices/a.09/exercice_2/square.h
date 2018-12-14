#pragma once
#ifndef SQARE_H
#define SQARE_H
/**
 * Programmation C: Design OO
 * solution de l'exercice 2
 */

#include "figure.h"

struct c_square {
    int m_x_axis;
    int m_y_axis;
    int m_length;
    struct c_figure m_base;
};

extern struct c_figure* square_init (struct c_square *square, int x_axis, int y_axis, int length);

extern int square_draw (struct c_figure *oref);
extern int square_move (struct c_figure *oref, int x_axis, int y_axis);
extern int square_resize (struct c_figure *oref, int x_percent, int y_percent);
extern int square_rotate (struct c_figure *oref, int angle);
extern int square_erase (struct c_figure *oref);
extern int square_show (struct c_figure *oref);

#endif
