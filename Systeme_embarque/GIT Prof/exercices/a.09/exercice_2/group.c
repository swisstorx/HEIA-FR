/**
 * Programmation C: Design OO
 * solution de l'exercice 2
 */
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "figure.h"
#include "group.h"


int group_draw (struct c_figure *oref)
{
	struct c_group* group = container_of (oref, struct c_group, m_base);
	struct element* ele = group->m_chain;
	printf("group(%p): draw\n", (void*)group);
	while (ele != 0) {
		ele->figure->m_draw(ele->figure);
		ele = ele->next;
	}
	return 0;
}


int group_move (struct c_figure *oref, int x_axis, int y_axis)
{
	struct c_group* group = container_of (oref, struct c_group, m_base);
	struct element* ele = group->m_chain;
	printf("group(%p): move x_axis:%d, y_axis:%d\n", (void*)group, x_axis, y_axis);
	while (ele != 0) {
		ele->figure->m_move(ele->figure, x_axis, y_axis);
		ele = ele->next;
	}
	return 0;
}

int group_resize (struct c_figure *oref, int x_percent, int y_percent)
{
	struct c_group* group = container_of (oref, struct c_group, m_base);
	struct element* ele = group->m_chain;
	printf("group(%p): resize x_percent:%d, y_percent:%d\n", (void*)group, x_percent, y_percent);
	while (ele != 0) {
		ele->figure->m_resize(ele->figure, x_percent, y_percent);
		ele = ele->next;
	}
	return 0;
}

int group_rotate (struct c_figure *oref, int angle)
{
	struct c_group* group = container_of (oref, struct c_group, m_base);
	struct element* ele = group->m_chain;
	printf("group(%p): rotate angle:%d\n", (void*)group, angle);
	while (ele != 0) {
		ele->figure->m_rotate(ele->figure, angle);
		ele = ele->next;
	}
	return 0;
}

int group_erase (struct c_figure *oref)
{
	struct c_group* group = container_of (oref, struct c_group, m_base);
	struct element* ele = group->m_chain;
	printf("group(%p): erase\n", (void*)group);
	while (ele != 0) {
		ele->figure->m_erase(ele->figure);
		ele = ele->next;
	}
	return 0;
}


int group_show (struct c_figure *oref)
{
	struct c_group* group = container_of (oref, struct c_group, m_base);
	struct element* ele = group->m_chain;
	printf("group(%p): show\n", (void*)group);
	while (ele != 0) {
		ele->figure->m_show(ele->figure);
		ele = ele->next;
	}
	return 0;
}


int group_add (struct c_group* group, struct c_figure* figure)
{
	struct element* ele = malloc (sizeof(*ele));
	memset (ele, 0, sizeof(*ele));
	ele->figure = figure;
	ele->next = 0;
	if (group->m_chain == 0) {
		group->m_chain = ele;
	} else {
		struct element* n = group->m_chain;
		while (n->next != 0) { 
			n = n->next;
		}
		n->next = ele;
	}
	return 0;
}

int group_remove (struct c_group* group, struct c_figure* figure)
{
	struct element* p = 0;
	struct element* n = group->m_chain;
	while ((n != 0) && (n->figure != figure)) {
		p = n;
		n = n->next;
	}
	if (n != 0) {
		if (p != 0) {
			p->next = n->next;
		} else {
			group->m_chain = n->next;
		}
		free (n);
	}
	return 0;
}


struct c_figure* group_init (struct c_group *group)
{
	figure_init (&group->m_base);

	group->m_base.m_draw   = group_draw;
	group->m_base.m_move   = group_move;
	group->m_base.m_resize = group_resize;
	group->m_base.m_rotate = group_rotate;
	group->m_base.m_erase  = group_erase;
	group->m_base.m_show   = group_show;
	group->m_add           = group_add;
	group->m_remove        = group_remove;

	group->m_chain = 0;

	return &group->m_base;
}

