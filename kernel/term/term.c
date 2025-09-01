#include "term.h"

#define TERM_MARGIN 25

uint16_t termX = 0;
uint16_t termY = 0;
uint16_t termXMax, termYMax;

uint32_t termGetWidth(void) {
    return gpuGetWidth()-TERM_MARGIN;
}

uint32_t termGetHeight(void) {
    return gpuGetHeight()-TERM_MARGIN;
}

// will use font colour and base it off the terminal start
void termPutPixel(uint16_t x, uint16_t y) {
    gpuPutPixel(0xFFFFFFFF, TERM_MARGIN+x, TERM_MARGIN+y);
}

// TODO: REAL FONT !!
void termPutc(char c) {
    if(c > 127) { // font currently doesnt support extended ascii
        miniuartSends("term: extended ascii '");
        miniuartSendc(c);
        miniuartSends("' is not supported by the font!\n");
        return;
    }

    if(c == '\n') {
        termY++;
        termX = 0;
        return;
    }

    // end of the row
    if(termX == termXMax) {
        termX = 0;
        termY++;
    }

    // no scrolling, keep it on the last line
    if(termY > termYMax) {
        termY = termYMax;
        termX = 0;
    }

    char* character = font[c];

    uint32_t startX = termX*8;
    uint32_t startY = termY*8;

    for(uint8_t y = 0; y<8; y++) {
        for(uint8_t x = 0; x<8; x++) {
            if(character[y] & 1 << x)
                termPutPixel(startX+x, startY+y);
        }
    }

    termX++;
}

void termInit(void) {
    gpuFillArea(0xFFDA9832, 0, 0, gpuGetWidth()-1, gpuGetHeight()-1);
    gpuFillArea(0xFF000000, TERM_MARGIN-1, TERM_MARGIN-1, termGetWidth()-1, termGetHeight()-1);

    // font size of 8
    termXMax = (termGetWidth()/8)-2;
    termYMax = (termGetHeight()/8)-2;

    miniuartSends("#terminal\n");
}
