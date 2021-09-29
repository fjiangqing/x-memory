/*******************************************************************************
* @Author       : Jon.Fang
* @Date         : 2021-09-28 13:48:50
* @LastEditors  : Jon.Fang
* @LastEditTime : 2021-09-29 09:06:04
* @FilePath     : /mmap/x_memory.c
* @Description  :
*******************************************************************************/
#include "x_memory.h"

typedef struct
{
    void              *memory_head_address;
    void              *memory_end_address;
    size_t            memory_free_size;
    size_t            memory_size;
    x_memory_status_t status;
} x_memory_info_t;

x_memory_info_t x_memory_info =
{
    .memory_head_address = NULL,
    .memory_end_address  = NULL,
    .memory_size         =             0,
    .status              = X_MEMORY_NULL,
};


typedef uint32_t x_malloc_head_size;

#define HEAD_RAM_SIZE_BIT    (sizeof(x_malloc_head_size) * 8 - 1)
typedef union
{
    struct
    {
        x_malloc_head_size current_ram_size : HEAD_RAM_SIZE_BIT;
        x_malloc_head_size current_ram_used : 1;
    }                  bit;
    x_malloc_head_size head;
} x_malloc_head_t;

#define CURRENT_RAM_UNUSED    0
#define CURRENT_RAM_USED      1

x_malloc_head_t *x_malloc_head;

x_memory_status_t x_memory_init(size_t memory_use_max_size)
{
    x_memory_info.memory_head_address = malloc(memory_use_max_size);
    if (x_memory_info.memory_head_address == NULL)
    {
        x_memory_info.status = X_MEMORY_INIT_ERR;
        return X_MEMORY_ERR;
    }

    x_memory_info.memory_size      = memory_use_max_size;
    x_memory_info.memory_free_size = memory_use_max_size;

    x_memory_info.memory_end_address = x_memory_info.memory_head_address + memory_use_max_size;

    x_malloc_head = x_memory_info.memory_head_address;

    x_malloc_head->bit.current_ram_used = CURRENT_RAM_UNUSED;

    x_malloc_head->bit.current_ram_size = memory_use_max_size;

    printf("x_memory_info.memory_free_size = %lu\r\n", x_memory_info.memory_free_size);

    x_memory_info.status = X_MEMORY_INIT_OK;

    return X_MEMORY_OK;
}


void *x_malloc(size_t size)
{
    x_malloc_head_t *x_malloc_head_index = x_memory_info.memory_head_address;

    x_malloc_head_t *x_malloc_head_next = NULL;

    size_t x_malloc_head_size = sizeof(x_malloc_head_t);

    void *malloc_point = NULL;

    printf("x_memory_info.memory_free_size = %lu\r\n", x_memory_info.memory_free_size);

    // todo:要求对齐
    size_t malloc_size = (size % MEMORY_ALIGN_SETTING == 0) ?  size : (size + MEMORY_ALIGN_SETTING - size % MEMORY_ALIGN_SETTING);

    while (x_malloc_head_index < x_memory_info.memory_end_address)
    {
        if ((x_malloc_head_index->bit.current_ram_used == CURRENT_RAM_UNUSED) &&
            (x_malloc_head_index->bit.current_ram_size >= malloc_size))
        {
            // 内存分配
            malloc_point = x_malloc_head_index + x_malloc_head_size;

            x_memory_info.memory_free_size -= x_malloc_head_size;
            x_memory_info.memory_free_size -= malloc_size;

            // 下一个节点
            x_malloc_head_next = (uint8_t *)x_malloc_head_index + malloc_size + x_malloc_head_size;
            // todo:末尾溢出判断?

            x_malloc_head_next->bit.current_ram_used = CURRENT_RAM_UNUSED;
            x_malloc_head_next->bit.current_ram_size = x_malloc_head_index->bit.current_ram_size - malloc_size - x_malloc_head_size;

            //当前节点
            x_malloc_head_index->bit.current_ram_size = malloc_size;
            x_malloc_head_index->bit.current_ram_used = CURRENT_RAM_USED;

            break;
        }
        else
        {
            // todo:内存分配失败
        }

        x_malloc_head_index = (uint8_t *)x_malloc_head_index + x_malloc_head_index->bit.current_ram_size;
        x_malloc_head_index = (uint8_t *)x_malloc_head_index + x_malloc_head_size;
    }

    return malloc_point;
}


void x_free(void *point)
{
    point = NULL;
}
