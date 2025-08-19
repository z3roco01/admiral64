#include "mailbox.h"

// first nybble gets set to the channel
void mailboxWrite(uint8_t ch, uint32_t data) {
    // actual data to write
    uint32_t chData = (data & 0xFFFFFFF0) | (ch & 0x0F);

    // wait until the full bit is clear
    while(*MAILBOX_STATUS & MAILBOX_FULL){asm volatile("nop");}

    *MAILBOX_WRITE = chData;
}

uint32_t mailboxRead(uint8_t ch) {
    while(1) {
        // wait until it has data
        while(*MAILBOX_STATUS & MAILBOX_EMPTY){asm volatile("nop");}

        // read new data and extra channel
        uint32_t data = *MAILBOX_READ;
        uint8_t readCh = (uint8_t)data & 0x0F;

        // if the data comes from the right channel, then return it, without the channel id
        if(readCh == ch)
            return data & 0xFFFFFFF0;
    }
}
