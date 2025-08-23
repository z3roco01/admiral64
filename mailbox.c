#include"mailbox.h"

void mailboxWrite(uint32_t value, uint8_t ch) {
    // add the channel to the last 4 bits
    uint32_t data = (value&~0xF) | (ch&0xF);
    // wait until the full flag is clear
    while(*MAILBOX_STATUS & MAILBOX_FULL){asm volatile("nop");}
    // write the data
    *MAILBOX_WRITE = data;
}

uint32_t mailboxRead(uint8_t ch) {
    while(1) {
        // wait until the empty flag is not set
        while(*MAILBOX_STATUS & MAILBOX_EMPTY){asm volatile("nop");}

        // read the data and extract the channel number
        uint32_t data = *MAILBOX_READ;
        uint8_t readCh = data & 0xF;

        // if the data is from the correct channel, return it
        if((ch&0xF) == readCh)
            return data&~0xF;
    }
}

// send a mailbox tag
uint8_t mailboxSendTag(uint32_t** tag) {
    // get the address of the tag correctly
    uint32_t data = (uint32_t)(uint64_t)tag;
    // write the address to the proper mailbox
    mailboxWrite(data, MAILBOX_CH_TAG);
    // wait until a response is given
    mailboxRead(MAILBOX_CH_TAG);

    return 1;
}
