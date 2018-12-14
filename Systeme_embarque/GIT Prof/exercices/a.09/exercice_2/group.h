#pragma once
#ifndef GROUP_H
#define GROUP_H
/**
 * Programmation C: Design OO
 * solution de l'exercice 2
 */

#include "figure.h"

struct element {
    struct c_figure* figure;
    struct element* next;
};

struct c_group
{
    struct c_figure m_base;
    struct element *m_chain;
    int (*m_add)   (struct c_group* group, struct c_figure* figure);
    int (*m_remove)(struct c_group* group, struct c_figure* figure);
};

extern struct c_figure* group_init (struct c_group *group);
extern int group_add (struct c_group* group, struct c_figure* figure);
extern int group_remove (struct c_group* group, struct c_figure* figure);

extern int group_draw (struct c_figure *oref);
extern int group_move (struct c_figure *oref, int x_axis, int y_axis);
extern int group_resize (struct c_figure *oref, int x_percent, int y_percent);
extern int group_rotate (struct c_figure *oref, int angle);
extern int group_erase (struct c_figure *oref);
extern int group_show (struct c_figure *oref);


#endif
