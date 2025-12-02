#include "hal/spi.h"
#include "hal/customWait.h"

static short C = 0;
// static short A = 0;
// static short B = 0;
// static short pA = 0;
// static short pB = 0;
// static short input = 0;
// static short state = 0;
int getEncoderInput(short chClick, short chLeft, short chRight) {
    C = spiRead(chClick, 250000) > 2000;
    if (spiRead(chLeft, 250000) - spiRead(chRight, 250000) > 2000) {
        while (spiRead(chRight, 250000) != 0 || spiRead(chLeft, 250000) != 0) {}
        Custom_wait(100);
        return 1 + (C << 1); // 1: left, 3: left+click
    } 
    else if (spiRead(chLeft, 250000) - spiRead(chRight, 250000) < -2000) {
        while (spiRead(chLeft, 250000) != 0 || spiRead(chRight, 250000) != 0) {}
        Custom_wait(100);
        return -1 - (C << 1); // -1: right, -3: right+click
    }
    else {
        return 0 + C*3;
    }
}