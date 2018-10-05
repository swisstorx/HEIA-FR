#ifndef SQUARE_H
#define SQUARE_H

/**
 * @ingroup infra_figures
 * @defgroup square Square
 * @{
 */


#include "figure.h"

struct square {
    struct point origin;	///< square position
    int length;			///< side length
    struct figure base;		///< figure base class
};

/**
 * Initialize all the resources of a square object
 * @param square reference to square object to be initialized
 * @param x_axis x axis position
 * @param y_axis y axis position
 * @param length side length
 * @return initialized figure object reference
 */
extern struct figure* square_init (struct square *square, int x_axis, int y_axis, int length);

/**
 * @}
 */


#endif
