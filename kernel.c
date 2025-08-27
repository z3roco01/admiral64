#include"uart.h"
#include"mailbox.h"
#include"gpu.h"

void kmain(uint64_t dtbPtr, uint64_t x1, uint64_t x2, uint64_t x3) {
    ((uint8_t*)0xA00000)[0] = 0x11;

    miniuartInit();

    miniuartSends("#setup miniuart\n");
    gpuInit();
    gpuPutPixel(0x0000FFFF, 0, 1);
    gpuFillArea(0x0000FFFF, 5, 10, 14, 28);

    while(1) {
        miniuartSendc(miniuartGetc());
    }
}
