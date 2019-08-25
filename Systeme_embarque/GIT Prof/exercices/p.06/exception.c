/**
 * Copyright 2016 University of Applied Sciences Western Switzerland / Fribourg
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Project: HEIA-FR / Embedded Systems 2 Laboratory
 *
 * Abstract:    ARM Exception Handling
 *
 * Author:  Daniel Gachet
 * Date:    27.02.2016
 */

#include <stdio.h>
#include "interrupt.h"

static void exception_handler(enum interrupt_vectors vector,
                              void* addr,
                              void* param)
{
    printf(
        "ARM Exception(%d): %s at address: %p\n", vector, (char*)param, addr);
    while (vector == INT_PREFETCH)
        ;
}

void exception_init()
{
    interrupt_attach(INT_UNDEF, exception_handler, "undefined instruction");
    interrupt_attach(INT_SWI, exception_handler, "software interrupt");
    interrupt_attach(INT_PREFETCH, exception_handler, "prefetch abort");
    interrupt_attach(INT_DATA, exception_handler, "data abort");
}
