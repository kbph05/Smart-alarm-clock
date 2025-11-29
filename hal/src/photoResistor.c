#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "./hal/spi.h"

static const int SPI_SPEED = 250000;

int readLightLevel(int channel) {
    int rawLightLevel = spiRead(channel, SPI_SPEED);
    return rawLightLevel;
}