#ifndef UART_H_
#define UART_H_

#include<stdint.h>
#include"mmio.h"
#include"gpio.h"

/* UART1 mini uart registers*/
#define AUX_ENABLES     ((volatile uint32_t*)(MMIO_BASE+0x215004))
#define AUX_MU_IO_REG   ((volatile uint32_t*)(MMIO_BASE+0x215040))
#define AUX_MU_IIR_REG  ((volatile uint32_t*)(MMIO_BASE+0x215044))
#define AUX_MU_LCR_REG  ((volatile uint32_t*)(MMIO_BASE+0x21504C))
#define AUX_MU_MCR_REG  ((volatile uint32_t*)(MMIO_BASE+0x215050))
#define AUX_MU_LSR_REG  ((volatile uint32_t*)(MMIO_BASE+0x215054))
#define AUX_MU_CNTL_REG ((volatile uint32_t*)(MMIO_BASE+0x215060))

void miniuartInit(void);
void miniuartSendc(char c);
void miniuartSends(char* str);
char miniuartGetc();

#endif // UART_H_
