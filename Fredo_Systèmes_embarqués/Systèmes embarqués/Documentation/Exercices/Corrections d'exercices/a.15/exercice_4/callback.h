#pragma once
#ifndef CALLBACK_H
#define CALLBACK_H
/* Interfacing C with assembleur
 * Exercice 4 : solution
 */

#include <stdint.h>
#include <stdbool.h>

/**
 * Define the maximum number of functions that could be attached
 */
#define MAX_NB_OF_FUNCTIONS	100

/**
 * Function prototype which could be attach to that library 
 *  
 * @param param value/pointer specified during attachment 
 * @param arg1 first argument 
 * @param arg2 second argument 
 * @param arg3 third argument 
 *  
 * @return status 0 successful, < 0 error 
 */
typedef int (*callback_function_t) (void* param, int arg1, int arg2, void* arg3);


/**
 * Method to initialize the call-back library.
 * This method should be called prior any other method.
 * 
 */
extern void callback_init ();


/**
 * Method to attach a function to the library.
 * 
 * @param key identification of the function which should be 
 *            used to call/detach it later on
 * @param fnct function to attach 
 * @param param value/pointer associated to the function, which 
 *               will be passed as first argument during calls
 * @return status: 0 successful, -1 error while attaching the
 *         function (too many functions already attached or key
 *         already used)
 */
extern int callback_attach (int key, callback_function_t fnct, void* param);

/**
 * Method to detach a function from the library
 * 
 * @param key associated to the function
 */
extern void callback_detach (int key);

/**
 * Method to call an attached function based on its key
 * 
 * @param key associated to the function to call
 * @param arg1 1st argument passed to the called function
 * @param arg2 2nd argument passed to the called function
 * @param arg3 3rd argument passed to the called function
 * 
 * @return status: 0 successful, -1 error while calling the function
 */
extern int callback_call (int key, int arg1, int arg2, void* arg3);

#endif
