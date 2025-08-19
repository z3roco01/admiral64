#ifndef GPIO_H_
#define GPIO_H_

#include<stdint.h>
#include"mmio.h"

#define GPFSEL0   ((volatile uint32_t*)MMIO_BASE+0x200000)
#define GPFSEL1   ((volatile uint32_t*)MMIO_BASE+0x200004)
#define GPFSEL2   ((volatile uint32_t*)MMIO_BASE+0x200008)
#define GPFSEL3   ((volatile uint32_t*)MMIO_BASE+0x20000C)
#define GPFSEL4   ((volatile uint32_t*)MMIO_BASE+0x200010)
#define GPFSEL5   ((volatile uint32_t*)MMIO_BASE+0x200014)
#define GPPUD     ((volatile uint32_t*)MMIO_BASE+0x200094)
#define GPPUDCLK0 ((volatile uint32_t*)MMIO_BASE+0x200098)
#define GPPUDCLK1 ((volatile uint32_t*)MMIO_BASE+0x20009C)

typedef enum gpFun {
    GPF_IN,
    GPF_OUT,
    GPF_ALT5,
    GPF_ALT4,
    GPF_ALT0,
    GPF_ALT1,
    GPF_ALT2,
    GPF_ALT3
} gpFun_t;

typedef enum gppudMode {
    GPPUD_OFF,
    GPPUD_DOWN,
    GPPUD_UP,
    GPPUD_RESERVED
} gppudMode_t;


void setPUDMode(int gpioNum, gppudMode_t mode);
void gpioSetFun(uint8_t gpioNum, gpFun_t fun);
#endif // GPIO_H_
