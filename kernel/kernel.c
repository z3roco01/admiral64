#include"drivers/uart/uart.h"
#include"drivers/mailbox/mailbox.h"
#include"drivers/gpu/gpu.h"
#include"term/term.h"

void kmain(uint64_t dtbPtr, uint64_t x1, uint64_t x2, uint64_t x3) {
    ((uint8_t*)0xA00000)[0] = 0x11;

    miniuartInit();

    miniuartSends("#setup miniuart\n");
    gpuInit();
    /*gpuPutPixel(0x0000FFFF, 0, 1);
    gpuFillArea(0x0000FFFF, 5, 10, 14, 28);
    for(uint32_t x = 0; x<640*4; x++) {
        for(uint32_t y = 0; x<480*4; x++)
            gpuPutPixel(0xFFFFFFFF, x, y);
    }*/
    for(uint32_t y = 0; y<480; y++) {
    	for(uint32_t x = 0; x<640; x++)
            gpuPutPixel(0xFFFFFFFF, x, y);
    }
    //termInit();

    while(1) {
        miniuartSendc(miniuartGetc());
    }
}
