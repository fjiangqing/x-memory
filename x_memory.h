/*******************************************************************************
* @Author       : Jon.Fang
* @Date         : 2021-09-28 13:48:57
* @LastEditors  : Jon.Fang
* @LastEditTime : 2021-09-29 09:11:16
* @FilePath     : /mmap/x_memory.h
* @Description  :
*******************************************************************************/

#ifndef X_MALLOC_H
#define X_MALLOC_H

#include "stdlib.h"
#include "stdint.h"

// #ifdef __x86_64__
//  #define MEMORY_ALIGN_SETTING    8
// #elif __i386__
//  #define MEMORY_ALIGN_SETTING    4
// #endif
#define MEMORY_ALIGN_SETTING    sizeof(int*)

typedef enum
{
    X_MEMORY_OK = 0,
    X_MEMORY_ERR,
    X_MEMORY_INIT_OK,
    X_MEMORY_INIT_ERR,
    X_MEMORY_NULL,
} x_memory_status_t;

x_memory_status_t x_memory_init(size_t memory_use_max_size);

void *x_malloc(size_t size);
void x_free(void *print);

#endif
