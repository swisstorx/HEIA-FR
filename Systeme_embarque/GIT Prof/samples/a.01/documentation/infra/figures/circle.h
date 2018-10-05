#ifndef CIRCLE_H
#define CIRCLE_H

/**
 * @ingroup infra_figures
 * @defgroup circle Circle
 * @{
 */

#include "figure.h"

/**
 * Circle...
 */
struct circle {
    struct point origin;	///< circle position
    int radius;			///< circle radius
    struct figure base;		///< figure base class
};

/**
 * Initialize all the resources of a circle object
 * @param circle reference to circle object to be initialized
 * @param x_axis x axis position
 * @param y_axis y axis position
 * @param radius circle radius
 * @return initialized figure object reference
 */
extern struct figure* circle_init (struct circle *circle, int x_axis, int y_axis, int radius);

/**
 * @}
 */


#endif
