#include "gpu.h"

static GPUInfo_t gpuInfo;

void gpuInit(void) {
    /* i COULD NOT get my structs to work no mater what, so frick it */
    // TODO: get them structs working
    uint32_t* payload __attribute__((aligned(16))) = (uint32_t*)(0xA0000);
    payload[0] = 35*4;
    payload[1] = MAILBOX_REQUEST;

    // set phy and virt size to 640x480
    payload[2] = MAILBOX_FB_SET_PHY_SIZE;
    payload[3] = 8;
    payload[4] = 8;
    payload[5] = 640; // x res
    payload[6] = 480; // y res

    payload[7] = MAILBOX_FB_SET_VIRT_SIZE;
    payload[8] = 8;
    payload[9] = 8;
    payload[10] = 640; // x res
    payload[11] = 480; // y res

    // reset virtual offset to 0
    payload[12] = MAILBOX_FB_SET_VIRT_OFF;
    payload[13] = 8;
    payload[14] = 8;
    payload[15] = 0; // x
    payload[16] = 0; // y

    // set color depth to 32 bits ( 8 per channel )32;
    payload[17] = MAILBOX_FB_SET_DEPTH;
    payload[18] = 4;
    payload[19] = 4;
    payload[20] = 32;

    // set pixel order to rgba instead of bgra
    payload[21] = MAILBOX_FB_SET_ORDER;
    payload[22] = 4;
    payload[23] = 4;
    payload[24] = 1;

    // allocate memory for the frame buffer ( idk what the base is bassed off of )
    payload[25] = MAILBOX_FB_ALLOC_FB; //get framebuffer, gets alignment on request
    payload[26] = 8;
    payload[27] = 4;
    payload[28] = 16; // base
    payload[29] = 0;  // size

    // get the pixels pitch
    payload[30] = MAILBOX_FB_GET_PITCH;
    payload[31] = 4;
    payload[32] = 4;
    payload[33] = 0;

    payload[34] = MAILBOX_TAG_LAST;

    mailboxSendTag(payload);

    payload[28]&=0x3FFFFFFF;   //convert GPU address to ARM address

    // may not get exactly the right parameters, so we store them and refer to them, rather than hardcoded
    gpuInfo.width  = payload[5];
    // stupid workaround since accessing payload[6] hangs
    gpuInfo.height = (uint32_t)(((uint64_t)payload[5]) & 0xFFFFFFFF);
    gpuInfo.rgba   = payload[24];
    gpuInfo.pitch  = payload[33];
    gpuInfo.fb     = (uint32_t*)((uint64_t)payload[28]);

    miniuartSends("#alloced a buffer for the gpu!\n");
    gpuInfo.fb[1]= 0xFF0000FF;
}

// will convert rgba to bgra only if needed
uint32_t toPixel(uint32_t colour) {
    return gpuInfo.rgba ? colour : ((colour & 0xFF) >> 8*2 | (colour&0xFF0000) | (colour & 0xFF00) << 8*2 | (colour&0x000000FF));
}

// colour should be passed in rgba
void gpuPutPixel(uint32_t colour, uint32_t x, uint32_t y) {
    // convert to bgra if needed
    uint32_t pixel = toPixel(colour);

    // ensure the coord will be winthin the range, will roll over
    uint32_t xCoord = x % gpuInfo.width+1;
    uint32_t yCoord = y % gpuInfo.height+1;

    gpuInfo.fb[x + (y*gpuInfo.height)] = pixel;
}

void gpuFillArea(uint32_t colour, uint32_t xCoord1, uint32_t yCoord1, uint32_t xCoord2, uint32_t yCoord2) {
    uint32_t pixel = toPixel(colour);

    // convert coords to proper range
    uint32_t x1 = xCoord1 % gpuInfo.width+1;
    uint32_t y1 = yCoord1 % gpuInfo.height+1;
    uint32_t x2 = xCoord2 % gpuInfo.width+1;
    uint32_t y2 = yCoord2 % gpuInfo.height+1;

    for(uint32_t y = y1; y<y2; y++) {
        for(uint32_t x = x1; x<x2; x++)
            gpuPutPixel(pixel, x, y);
    }
}
