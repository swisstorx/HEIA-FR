#pragma once
#ifndef CIRCLE_H
#define CIRCLE_H
/**
 * Programmation C: Design OO
 * solution de l'exercice 2
 */

#include "figure.h"

struct c_circle {
	struct point m_origin;
	int m_radius;
	struct c_figure m_base;
};

extern struct c_figure* circle_init (struct c_circle *circle, int x_axis, int y_axis, int radius);

extern int circle_draw (struct c_figure *oref);
extern int circle_move (struct c_figure *oref, int x_axis, int y_axis);
extern int circle_resize (struct c_figure *oref, int x_percent, int y_percent);
extern int circle_rotate (struct c_figure *oref, int angle);
extern int circle_erase (struct c_figure *oref);
extern int circle_show (struct c_figure *oref);

#endif
