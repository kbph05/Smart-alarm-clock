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
#include "clock.h"
#include "weather.h"
#include "calendar.h"

#define i2c_node_address 0x3c

// uint8_t time_FrameBuffer[1024];

uint8_t bar[72] = {
    0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b10000000, 0b10000000, 0b10000000, 0b10000000, 0b10000000, 0b10000000, 0b10000000, 0b10000000,
    0b11000000, 0b11000000, 0b11000000, 0b11000000, 0b11000000, 0b11000000, 0b11000000, 0b11000000,
    0b11100000, 0b11100000, 0b11100000, 0b11100000, 0b11100000, 0b11100000, 0b11100000, 0b11100000,
    0b11110000, 0b11110000, 0b11110000, 0b11110000, 0b11110000, 0b11110000, 0b11110000, 0b11110000,
    0b11111000, 0b11111000, 0b11111000, 0b11111000, 0b11111000, 0b11111000, 0b11111000, 0b11111000,
    0b11111100, 0b11111100, 0b11111100, 0b11111100, 0b11111100, 0b11111100, 0b11111100, 0b11111100,
    0b11111110, 0b11111110, 0b11111110, 0b11111110, 0b11111110, 0b11111110, 0b11111110, 0b11111110,
    0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111
};

void dispClock(rtc_t* clock) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    clock->hour = tm.tm_hour;
    clock->min = tm.tm_min;
    clock->day = tm.tm_mday;
    clock->month = tm.tm_mon + 1;
    clock->year = tm.tm_year + 1990;
    clock->isPm = 0;

    if (clock->hour > 12) {
        clock->hour -= 12;
        clock->isPm = 1;
    }

    char* timeString = malloc(8*sizeof(char));
    char* dateString = malloc(32*sizeof(char));
    sprintf(timeString, "%02i:%02i", clock->hour, clock->min);
    sprintf(dateString, "Sat, Nov %i     ", clock->day);
    if (clock->isPm) {
        strcat(timeString, "pm");
    } else {
        strcat(timeString, "am");
    }

    SSD1780_print2Buffer(3, dateString);
    SSD1780_print2BufferLarge(0, timeString);
    SSD1780_displayBuffer();
    free(timeString);
    free(dateString);
}

void dispWeatherForcast() {
    uint8_t forcast[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int index = 0;

    SSD1780_print2Buffer(3, "Forcast:       ");
    SSD1780_print2Buffer(1, "               ");    
    
    for (int charColumn = 1; charColumn < 15; charColumn+=2) {
        for (int i = 1; i < 8; i++) { 
            if ((8*i+8)+1+(64*charColumn) > 1024) {
                break;
            }
            frame_buffer[(8*i+8)+1+(64*charColumn)] = bar[forcast[index]*8+i];
        }  
        index++;
    }

    SSD1780_print2Buffer(0, " S M T W T F S ");
    SSD1780_displayBuffer();
}

int main() {   
    // Setup
    _i2c_init(1, i2c_node_address);
    SSD1780_defaultConfig();
    rtc_t* clock = initClock();

    while (1) {
        dispClock(clock);
        Custom_wait(1000);
        dispWeatherForcast();
        Custom_wait(1000);
    }

    _i2c_close();
    closeClock(clock);
    return 0;
}