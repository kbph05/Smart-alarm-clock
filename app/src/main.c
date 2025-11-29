/*

*/ 
// Standard Libraries
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

// #include <pthread.h>

// Hardware Abstraction Layers
#include "hal/spi.h"
#include "hal/encoder.h"
#include "hal/i2c.h"
#include "hal/customWait.h"
#include "hal/SSD1780.h"

// Additional Libraries

#define i2c_node_address 0x3c
// uint8_t data_buf[1025];


struct clock {
    int hour;
    int min;
};

void dispClock(struct clock time) {
    char* string = malloc(8*sizeof(char));
    sprintf(string, "%02i:%02i", time.hour, time.min);
    // memcpy(frame_buffer, interface_clock, 1024);
    SSD1780_print2BufferLarge(1, string);
    free(string);
}

int main() {   
    // Setup
    _i2c_init(1, i2c_node_address);
    SSD1780_defaultConfig();
    SSD1780_displayBuffer();

    _i2c_close();
    return 0;
}