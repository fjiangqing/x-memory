/*******************************************************************************
* @Author       : Jon.Fang
* @Date         : 2021-09-25 15:51:27
* @LastEditors  : Jon.Fang
* @LastEditTime : 2021-09-29 09:08:54
* @FilePath     : /mmap/test_main.c
* @Description  :
*******************************************************************************/
#include "stdio.h"

#include "stdlib.h"

#include "x_memory.h"

#include "string.h"

#define X_MEMORY_HEAP    128//1024 * 1024 * 10

int main(void)
{
    char hello[] = "hello x_malloc\r\n";

    x_memory_init(X_MEMORY_HEAP);

    char *x_buffer = NULL;//x_malloc(sizeof(hello));

    printf("sizeof(int*) = %lu\r\n", sizeof(int*));

    int i = 0;
    do
    {
        x_buffer = x_malloc(8);
        ++i;
        printf("i = %d\r\n", i);
        if (x_buffer != NULL)
        {
            memcpy(x_buffer, hello, sizeof(hello));
            printf("x_buffer = %s", x_buffer);
        }
    } while (x_buffer != NULL);

    return 0;
}
