#define _GNU_SOURCE

#include "hal/encoder.h"

int getEncoderInput() {
    if (spiRead(1, 250000) - spiRead(2, 250000) > 1000) {
        while (spiRead(2, 250000) != 0 || spiRead(1, 250000) != 0) {}
        Custom_wait(100);
        return 1;
    } 
    else if (spiRead(1, 250000) - spiRead(2, 250000) < -1000) {
        while (spiRead(1, 250000) != 0 || spiRead(2, 250000) != 0) {}
        Custom_wait(100);
        return -1;
    }
    return 0;
}