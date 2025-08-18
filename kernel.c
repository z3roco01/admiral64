#include"uart.h"

void kmain() {
    ((uint8_t*)0xA00000)[0] = 0x11;

    miniuartInit();

    miniuartSends("hey faz gang\nyo\n");

    while(1) {
        miniuartSendc(miniuartGetc());
    }
}
