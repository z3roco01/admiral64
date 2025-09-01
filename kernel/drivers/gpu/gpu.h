#ifndef GPU_H_
#define GPU_H_

#include<stdint.h>
#include"../mailbox/mailbox.h"

// gpu mailbox structures
// allocate memory space for the buffer
typedef struct mailboxFBAlloc {
    mailboxTag_t tag;
    uint32_t base; // base of the buffer ( based on what ? )
    uint32_t size; // allocated size, set after sent
} __attribute__((aligned(16))) __attribute__((packed)) mailboxFBAlloc_t;

// pitch between each pixel
typedef struct mailboxFBPitch {
    mailboxTag_t tag;
    uint32_t pitch; // Bits Per Pixel
} __attribute__((aligned(16))) __attribute__((packed)) mailboxFBPitch_t;

// both physical and virtual size set
typedef struct mailboxFBSize {
    mailboxTag_t tag;
    uint32_t xRes;
    uint32_t yRes;
} __attribute__((aligned(16))) __attribute__((packed)) mailboxFBSize_t;

// sets bits per pixel
typedef struct mailboxFBDepth {
    mailboxTag_t tag;
    uint32_t bpp; // Bits Per Pixel
} __attribute__((aligned(16))) __attribute__((packed)) mailboxFBDepth_t;

// pixel order ( 1 for rbg, 0 for bgr )
typedef struct mailboxFBOrder {
    mailboxTag_t tag;
    uint32_t order; // Bits Per Pixel
} __attribute__((aligned(16))) __attribute__((packed)) mailboxFBOrder_t;

// offset from the virtual image ( the vc can handle very large images )
typedef struct mailboxFBOff {
    mailboxTag_t tag;
    uint32_t xOff;
    uint32_t yOff;
} __attribute__((aligned(16))) __attribute__((packed)) mailboxFBOff_t;

// master list of all needed tags
typedef struct mailboxFBTags {
    mailboxFBSize_t  phySize;  // the requested physical size
    mailboxFBSize_t  virtSize; // the requested virtual size
    mailboxFBOff_t   off;      // virtual offset
    mailboxFBDepth_t depth;    // pixel depth in bits
    mailboxFBOrder_t order;    // requested colour order
    mailboxFBAlloc_t alloc;    // the allocated buffer
    mailboxFBPitch_t pitch;    // the pitch of the pixels
    uint32_t end;
} __attribute__((aligned(16))) __attribute__((packed)) mailboxFBTags_t;

// stores all the gpu info
typedef struct GPUInfo {
    uint32_t* fb;
    uint32_t width;
    uint32_t height;
    uint32_t rgba; // if 1 order is rgba, if 0 bgra
    uint32_t pitch;
} GPUInfo_t;

void gpuInit(void);
// colour should be passed in rgba
void gpuPutPixel(uint32_t colour, uint32_t x, uint32_t y);
void gpuFillArea(uint32_t colour, uint32_t xCoord1, uint32_t yCoord1, uint32_t xCoord2, uint32_t yCoord2);
void gpuFillScreen(uint32_t colour);
uint32_t gpuGetX(void);
uint32_t gpuGetY(void);

#endif // GPU_H_
