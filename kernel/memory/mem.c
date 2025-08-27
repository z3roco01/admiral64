#include "mem.h"

// simple memory copy
void memcpy(uint64_t n, void* dest, void* src) {
    for(uint64_t i = 0; i<n; i++)
        ((uint8_t*)dest)[i] = ((uint8_t*)src)[i];
}
