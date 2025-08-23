#include"uart.h"
#include"mailbox.h"
#include"homer.h"

unsigned int width, height, pitch, isrgb;   /* dimensions and channel order */
unsigned char *lfb;
volatile uint32_t  __attribute__((aligned(16))) fbox[36];

void lfb_init()
{
    fbox[0] = 35*4;
    fbox[1] = MAILBOX_REQUEST;

    fbox[2] = 0x48003;  //set phy wh
    fbox[3] = 8;
    fbox[4] = 8;
    fbox[5] = 640;         //FrameBufferInfo.width
    fbox[6] = 480;          //FrameBufferInfo.height

    fbox[7] = 0x48004;  //set virt wh
    fbox[8] = 8;
    fbox[9] = 8;
    fbox[10] = 640;        //FrameBufferInfo.virtual_width
    fbox[11] = 480;         //FrameBufferInfo.virtual_height

    fbox[12] = 0x48009; //set virt offset
    fbox[13] = 8;
    fbox[14] = 8;
    fbox[15] = 0;           //FrameBufferInfo.x_offset
    fbox[16] = 0;           //FrameBufferInfo.y.offset

    fbox[17] = 0x48005; //set depth
    fbox[18] = 4;
    fbox[19] = 4;
    fbox[20] = 32;          //FrameBufferInfo.depth

    fbox[21] = 0x48006; //set pixel order
    fbox[22] = 4;
    fbox[23] = 4;
    fbox[24] = 1;           //RGB, not BGR preferably

    fbox[25] = 0x40001; //get framebuffer, gets alignment on request
    fbox[26] = 8;
    fbox[27] = 8;
    fbox[28] = 4096;        //FrameBufferInfo.pointer
    fbox[29] = 0;           //FrameBufferInfo.size

    fbox[30] = 0x40008; //get pitch
    fbox[31] = 4;
    fbox[32] = 4;
    fbox[33] = 0;           //FrameBufferInfo.pitch

    fbox[34] = MAILBOX_TAG_LAST;

    //this might not return exactly what we asked for, could be
    //the closest supported resolution instead
    if(mailboxSendTag((uint32_t**)&fbox)) {
        miniuartSends("fert\n");
        fbox[28]&=0x3FFFFFFF;   //convert GPU address to ARM address
        width=fbox[5];          //get actual physical width
        height=fbox[6];         //get actual physical height
        pitch=fbox[33];         //get number of bytes per line
        isrgb=fbox[24];         //get the actual channel order
        lfb=(void*)((unsigned long)fbox[28]);
    } else {
        miniuartSends("Unable to set screen resolution to 640x480x32\n");
    }
        miniuartSends("dookie\n");
}


void kmain() {
    ((uint8_t*)0xA00000)[0] = 0x11;

    miniuartInit();

    miniuartSends("hey faz gang\n");
    lfb_init();

    while(1) {
        miniuartSendc(miniuartGetc());
    }
}
