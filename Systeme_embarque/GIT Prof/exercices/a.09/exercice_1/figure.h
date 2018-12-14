#pragma once
#ifndef FIGURE_H
#define FIGURE_H
/**
 * Programmation C: Design OO
 * solution de l'exercice 1
 */

struct c_figure {
	int (*m_draw)   (struct c_figure* oref);
	int (*m_move)   (struct c_figure* oref, int x_axis,    int y_axis);
	int (*m_resize) (struct c_figure* oref, int x_percent, int y_percent);
	int (*m_rotate) (struct c_figure* oref, int angle);
	int (*m_erase)  (struct c_figure* oref);
	int (*m_show)   (struct c_figure* oref);
};

extern struct c_figure* figure_init (struct c_figure *fig);

extern int figure_draw (struct c_figure *oref);
extern int figure_move (struct c_figure *oref, int x_axis, int y_axis);
extern int figure_resize (struct c_figure *oref, int x_percent, int y_percent);
extern int figure_rotate (struct c_figure *oref, int angle);
extern int figure_erase (struct c_figure *oref);
extern int figure_show (struct c_figure *oref);

#endif
