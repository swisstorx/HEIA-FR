#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "figure.h"
#include "group.h"


#define container_of(ptr, type, member)\
((type*) ((char*)(ptr) - offsetof(type, member)))


static int group_draw (struct figure *self)
{
    struct group* group = container_of (self, struct group, base);
    struct element* ele = group->chain;
    printf("group(%p): draw\n", group);
    while (ele != 0) {
        ele->figure->draw(ele->figure);
        ele = ele->next;
    }
    return 0;
}


static int group_move (struct figure *self, int x_axis, int y_axis)
{
    struct group* group = container_of (self, struct group, base);
    struct element* ele = group->chain;
    printf("group(%p): move x_axis:%d, y_axis:%d\n", group, x_axis, y_axis);
    while (ele != 0) {
        ele->figure->move(ele->figure, x_axis, y_axis);
        ele = ele->next;
    }
    return 0;
}

static int group_resize (struct figure *self, int x_percent, int y_percent)
{
    struct group* group = container_of (self, struct group, base);
    struct element* ele = group->chain;
    printf("group(%p): resize x_percent:%d, y_percent:%d\n", group, x_percent, y_percent);
    while (ele != 0) {
        ele->figure->resize(ele->figure, x_percent, y_percent);
        ele = ele->next;
    }
    return 0;
}

static int group_rotate (struct figure *self, int angle)
{
    struct group* group = container_of (self, struct group, base);
    struct element* ele = group->chain;
    printf("group(%p): rotate angle:%d\n", group, angle);
    while (ele != 0) {
        ele->figure->rotate(ele->figure, angle);
        ele = ele->next;
    }
    return 0;
}

static int group_erase (struct figure *self)
{
    struct group* group = container_of (self, struct group, base);
    struct element* ele = group->chain;
    printf("group(%p): erase\n", group);
    while (ele != 0) {
        ele->figure->erase(ele->figure);
        ele = ele->next;
    }
    return 0;
}


static int group_show (struct figure *self)
{
    struct group* group = container_of (self, struct group, base);
    struct element* ele = group->chain;
    printf("group(%p): show\n", group);
    while (ele != 0) {
        ele->figure->show(ele->figure);
        ele = ele->next;
    }
    return 0;
}


int group_add (struct group* group, struct figure* figure)
{
    struct element* ele = malloc (sizeof(*ele));
    memset (ele, 0, sizeof(*ele));
    ele->figure = figure;
    ele->next = 0;
    if (group->chain == 0) {
        group->chain = ele;
    } else {
        struct element* n = group->chain;
        while (n->next != 0) {
            n = n->next;
        }
        n->next = ele;
    }
    return 0;
}

int group_remove (struct group* group, struct figure* figure)
{
    struct element* p = 0;
    struct element* n = group->chain;
    while ((n != 0) && (n->figure != figure)) {
        p = n;
        n = n->next;
    }
    if (n != 0) {
        if (p != 0) {
            p->next = n->next;
        } else {
            group->chain = n->next;
        }
        free (n);
    }
    return 0;
}


struct figure* group_init (struct group *group)
{
    figure_init (&group->base);

    group->base.draw   = group_draw;
    group->base.move   = group_move;
    group->base.resize = group_resize;
    group->base.rotate = group_rotate;
    group->base.erase  = group_erase;
    group->base.show   = group_show;
    group->add         = group_add;
    group->remove      = group_remove;

    group->chain = 0;

    return &group->base;
}

