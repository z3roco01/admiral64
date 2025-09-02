#ifndef MM_H_
#define MM_H_

#include<stdint.h>

typedef struct {
    uint8_t flags;
    uint32_t size;
    void* data;
} memBlk_t;

void mmInit();

#endif // MM_H_
