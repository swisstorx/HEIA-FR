#pragma once
#ifndef SVC_H
#define SVC_H
/* Interrupt handling
 * Exercice 4 : solution
 */

#include <stdlib.h>

typedef int (*svc_handler_t) (int table, int fnct);

extern void svc_init (void* stack, size_t stack_size);
extern int svc_1_call (int fnct);
extern int svc_5_call (int fnct);

#endif
