#ifndef MAILBOX_H_
#define MAILBOX_H_

#include<stdint.h>
#include"mmio.h"

// base address for the mailbox
#define MAILBOX_BASE ((volatile uint32_t*)MMIO_BASE+0xB880)
// mailbox registers
#define MAILBOX_READ   MAILBOX_BASE
#define MAILBOX_STATUS ((volatile uint32_t*)MAILBOX_BASE+0x18)
#define MAILBOX_WRITE  ((volatile uint32_t*)MAILBOX_BASE+0x20)

// status values
#define MAILBOX_EMPTY 0x40000000
#define MAILBOX_FULL  0x80000000

// 8 mailbox channels
#define MAILBOX_CH_POWER  0 // Mailbox channel 0: power interface
#define MAILBOX_CH_FB     1 // Mailbox channel 1: gpu framebuffer interface
#define MAILBOX_CH_UART   2 // Mailbox channel 2: UART0 interface
#define MAILBOX_CH_VCHIQ  3 // Mailbox channel 3: VCHIQ interface
#define MAILBOX_CH_LED    4 // Mailbox channel 4: leds interface
#define MAILBOX_CH_BUTTON 5 // Mailbox channel 5: buttons interface
#define MAILBOX_CH_TOUCH  6 // Mailbox channel 6: touch screen interface
#define MAILBOX_CH_TAG    7 // Mailbox channel 7: ARM -> VC tag interface

#endif // MAILBOX_H_
