#include"drivers/uart/uart.h"
#include"drivers/mailbox/mailbox.h"
#include"drivers/gpu/gpu.h"
#include"term/term.h"

void kmain(uint64_t dtbPtr, uint64_t x1, uint64_t x2, uint64_t x3) {
    ((uint8_t*)0xA00000)[0] = 0x11;

    miniuartInit();

    miniuartSends("#setup miniuart\n");
    gpuInit();
    termInit();

    char c;
    while(1) {
        c = miniuartGetc();
        miniuartSendc(c);
        termPutc(c);
    }
}
