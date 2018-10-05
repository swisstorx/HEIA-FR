#ifndef TRAPEZE_H
#define TRAPEZE_H

/**
 * @ingroup infra_figures
 * @defgroup trapeze Trapeze
 * @{
 */


#include "figure.h"

/**
 * Trapeze...
 */
struct trapeze {
    struct point p1_origin;	///< point 1 position
    struct point p2_origin;	///< point 2 position
    struct point p3_origin;	///< point 3 position
    struct point p4_origin;	///< point 4 position
    struct figure base;		///< figure base class
};

/**
 * Initialize all the resources of a trapeze object
 * @param trapeze reference to trapeze object to be initialized
 * @param p1_x_axis point 1 x axis position
 * @param p1_y_axis point 1 y axis position
 * @param p2_x_axis point 2 x axis position
 * @param p2_y_axis point 2 y axis position
 * @param p3_x_axis point 3 x axis position
 * @param p3_y_axis point 3 y axis position
 * @param p4_x_axis point 4 x axis position
 * @param p4_y_axis point 4 y axis position
 * @return initialized figure object reference
 */
extern struct figure* trapeze_init (struct trapeze *trapeze,
                                    int p1_x_axis, int p1_y_axis,
                                    int p2_x_axis, int p2_y_axis,
                                    int p3_x_axis, int p3_y_axis,
                                    int p4_x_axis, int p4_y_axis);

/**
 * @}
 */


#endif
