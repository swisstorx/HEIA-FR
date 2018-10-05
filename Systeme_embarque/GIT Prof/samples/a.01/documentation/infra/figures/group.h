#ifndef GROUP_H
#define GROUP_H

/**
 * @ingroup infra_figures
 * @defgroup group Group
 * @{
 */

/**
 * Elements...
 */
struct element {
    struct figure* figure;	///< reference to figure object
    struct element* next;	///< reference to next figure in the chain
};

struct group;
typedef int (*group_add_remove_t) (struct group* group, struct figure* figure);

/**
 * Group...
 */
struct group {
    struct figure base;		///< figure base class
    struct element *chain;	///< chaining reference
    group_add_remove_t add;	///< add a new figure to the group
    group_add_remove_t remove;	///< remove a figure from the group
};

extern struct figure* group_init (struct group *group);

/**
 * @}
 */


#endif
