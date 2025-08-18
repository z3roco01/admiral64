#include "gpio.h"

void setPUDMode(int gpioNum, gppudMode_t mode) {
    volatile uint32_t* gppudClkReg;

    if(gpioNum <= 31)
        gppudClkReg = GPPUDCLK0;
    else if(gpioNum <= 53)
        gppudClkReg = GPPUDCLK1;
    else
        return;


    // set new pull method to off
    *GPPUD = 0;

    int i = 150;
    // wait required 150 cycles
    while(i--) {asm volatile("nop");}
    // after signal has settled set pin that will have their mode to be changed
    *gppudClkReg = 1 << (gpioNum % 32);
    // wait another required 150 cycles
    i = 150; while(i--) {asm volatile("nop");}
    // then write = GPPUD and GPUDCLKX to remove signals
    *GPPUD = 0;
    *gppudClkReg = 0;
}

void gpioSetFun(uint8_t gpioNum, gpFun_t fun) {
    volatile uint32_t* gpfselReg;

    if(gpioNum <= 9)
        gpfselReg = GPFSEL0;
    else if(gpioNum <= 19)
        gpfselReg = GPFSEL1;
    else if(gpioNum <= 29)
        gpfselReg = GPFSEL2;
    else if(gpioNum <= 39)
        gpfselReg = GPFSEL3;
    else if(gpioNum <= 49)
        gpfselReg = GPFSEL4;
    else if(gpioNum <= 53)
        gpfselReg = GPFSEL5;
    else // gpio pin number is too high
        return;

    // shift the function select over by the relative number * 3
    (*gpfselReg) |= fun << (gpioNum % 10)*3;

    // only needed for alt functions
    if(fun > 1)
        // disable pull up/down on this pin
        setPUDMode(gpioNum, GPPUD_OFF);
}
