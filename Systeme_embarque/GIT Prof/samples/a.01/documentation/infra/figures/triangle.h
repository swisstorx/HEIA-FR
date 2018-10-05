#ifndef TRIANGLE_H
#define TRIANGLE_H

/**
 * @ingroup infra_figures
 * @defgroup triangle Triangle
 * @{
 *
 * Sample code to create a circle object...
 * @code
 *	struct triangle* triangle = calloc (1, sizeof(struct triangle));
 *	struct figure* fig = triangle_init(triangle, 0,0, 0,10, 10,10);
 *	fig->draw();
 * @endcode
 */


#include "figure.h"

/**
 * Triangle...
 */
struct triangle {
    struct point p1_origin;	///< point 1 position
    struct point p2_origin;	///< point 2 position
    struct point p3_origin;	///< point 3 position
    struct figure base;		///< figure base class
};

/**
 * Initialize all the resources of a triangle object
 * @param triangle reference to triangle object to be initialized
 * @param p1_x_axis point 1 x axis position
 * @param p1_y_axis point 1 y axis position
 * @param p2_x_axis point 2 x axis position
 * @param p2_y_axis point 2 y axis position
 * @param p3_x_axis point 3 x axis position
 * @param p3_y_axis point 3 y axis position
 * @return initialized figure object reference
 */

extern struct figure* triangle_init (struct triangle *triagle,
                                     int p1_x_axis, int p1_y_axis,
                                     int p2_x_axis, int p2_y_axis,
                                     int p3_x_axis, int p3_y_axis);

/**
 * @}
 */


#endif
