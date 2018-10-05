#ifndef FIGURE_H
#define FIGURE_H

/**
 * @ingroup infra_figures
 * @defgroup figure Figure
 * @{
 */

struct figure;  /* forward declaration to satisfy compiler version */

typedef int (*figure_draw_t)   (struct figure* self);
typedef int (*figure_move_t)   (struct figure* self, int x_axis,    int y_axis);
typedef int (*figure_resize_t) (struct figure* self, int x_percent, int y_percent);
typedef int (*figure_rotate_t) (struct figure* self, int angle);
typedef int (*figure_erase_t)  (struct figure* self);
typedef int (*figure_show_t)   (struct figure* self);

/**
 * Figure...
 */
struct figure {
    figure_draw_t   draw;	///< draw a figure
    figure_move_t   move;	///< move a figure
    figure_resize_t resize;	///< resize a figure
    figure_rotate_t rotate;	///< rotate a figure
    figure_erase_t  erase;	///< erase a figure
    figure_show_t   show;	///< show figure characteristics
};

/**
 * Point...
 */
struct point {
    int x_axis;  ///< x axis position
    int y_axis;  ///< y axis position
};

/**
 * Initialize all the resources of a figure object
 * @param fig reference to figure object to be initialized
 * @return initialized figure object reference
 */
extern struct figure* figure_init (struct figure *fig);

/**
 * @}
 */

#endif
