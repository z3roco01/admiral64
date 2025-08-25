#include"uart.h"
#include"mailbox.h"
#include"gpu.h"

void kmain() {
    ((uint8_t*)0xA00000)[0] = 0x11;

    miniuartInit();

    miniuartSends("#setup miniuart\n");
    gpuInit();
    gpuPutPixel(0x0000FFFF, 0, 1);

    while(1) {
        miniuartSendc(miniuartGetc());
    }
}
