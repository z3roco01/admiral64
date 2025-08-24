#ifndef MAILBOX_H_
#define MAILBOX_H_

#include<stdint.h>
#include"uart.h"
#include"gpio.h"

#define MAILBOX_REQUEST    0

// channels
#define MAILBOX_CH_POWER   0
#define MAILBOX_CH_FB      1
#define MAILBOX_CH_VUART   2
#define MAILBOX_CH_VCHIQ   3
#define MAILBOX_CH_LEDS    4
#define MAILBOX_CH_BTNS    5
#define MAILBOX_CH_TOUCH   6
#define MAILBOX_CH_COUNT   7
#define MAILBOX_CH_TAG     8

// mailbox addresses
#define MAILBOX_BASE    (MMIO_BASE+0xB880)
#define MAILBOX_READ    ((volatile unsigned int*)(MAILBOX_BASE))
#define MAILBOX_STATUS  ((volatile unsigned int*)(MAILBOX_BASE+0x18))
#define MAILBOX_WRITE   ((volatile unsigned int*)(MAILBOX_BASE+0x20))

// flag masks
#define MAILBOX_RESPONSE   0x80000000
#define MAILBOX_FULL       0x80000000
#define MAILBOX_EMPTY      0x40000000

// tag constants
#define MAILBOX_TAG_LAST           0

// mailbox enums
typedef enum mailboxTagId {
    MAILBOX_FB_SET_PHY_SIZE = 0x48003,
} mailboxTagId_t;

// mailbox structs
typedef struct mailboxTag {
    uint32_t id;
    uint32_t bufSize;
    uint32_t valLen;
} __attribute__((aligned(16))) __attribute__((packed)) mailboxTag_t;

typedef struct mailboxPayload {
    uint32_t size; // in bytes
    uint32_t code; // should be MAILBOX_REQUEST i think
    mailboxTag_t* tags;
} __attribute__((aligned(16))) __attribute__((packed)) mailboxPayload_t;

uint8_t mailboxSendTag(void* tag);

#endif // MAILBOX_H_
