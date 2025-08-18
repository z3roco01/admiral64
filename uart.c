#include"uart.h"

void enableMiniuart(void) {
    // make the uart accessible from the gpio pins
    gpioSetFun(14, GPF_ALT5);
    gpioSetFun(15, GPF_ALT5);

    // set the first bit, which enables mini uart
    *AUX_ENABLES |= 1;
}

void miniuartInit(void) {
    enableMiniuart();

    // disable interrupts
    *AUX_MU_IIR_REG = 0;
    // clear control registers, and enable 8 bit mode
    *AUX_MU_LCR_REG = 1; // 8 bit mode
    *AUX_MU_MCR_REG = 0;
    // clear extra control
    *AUX_MU_CNTL_REG = 0;
}

void miniuartSendc(char c) {
    // wait until the empty bit is set
    while(!(*AUX_MU_LSR_REG&0x20)) {
        asm volatile("nop"); // may be optimized to nothing if its empty
    }
    // set the io register to the character to send it
    *AUX_MU_IO_REG = c;
}

void miniuartSends(char* str) {
    char* s = str; // copy of pointer to not mess with input

    while(*s) { // loop until null
        // send the next character then increment the pointer
        miniuartSendc(*s++);
    }
}

char miniuartGetc() {
    // wait until the first bit is set
    while(!(*AUX_MU_LSR_REG&1)) {
        asm volatile("nop"); // may be optimized to nothing if its empty
    }

    return (char)*AUX_MU_IO_REG;
}
