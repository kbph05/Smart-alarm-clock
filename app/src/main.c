/*

*/ 
// Standard Libraries
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <setjmp.h>

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

// Threads
pthread_t encoder;
const int MAX_TAB = 1;
int cur_tab = 0;
int dispDay = 0;

#define DEBUG true

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

void dispClock(rtc_t* clock_m) {
    SSD1780_clearBuffer();
    char* dotw[7] = {"Sun", "Mon", "Tues", "Wed", "Thur", "Fri", "Sat"};
    char* month[14] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    char* timeString = malloc(8*sizeof(char));
    char* dateString = malloc(32*sizeof(char));
    sprintf(timeString, "%02i:%02i", clock_m->hour, clock_m->min);
    sprintf(dateString, "%s %s %02i, %i", dotw[clock_m->dotw], month[clock_m->month], clock_m->day, clock_m->year);
    if (clock_m->isPm) {
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

void dispWeatherForcast(rtc_t* clock_m) {
    SSD1780_clearBuffer();
    // uint8_t forcast[7] = {1, 2, 3, 4, 5, 6, 7};
    // int index = 0;
    
    // int condition[7] = {1, 2, 3, 4, 5, 6, 7};
    int tempHigh[7] = {11, 22, 33, 44, 55, 66, 77};
    int tempLow[7] = {00, 11, 22, 33, 44, 55, 66};



    // char* line3 = malloc(sizeof(char)*16);

    // strcpy(line3, condition[dispDay]);
    // SSD1780_print2Buffer(0, line3);
    
    // for (int charColumn = 1; charColumn < 15; charColumn+=2) {
    //     for (int i = 1; i < 8; i++) { 
    //         if ((8*i+8)+1+(64*charColumn) > 1024) {
    //             break;
    //         }
    //         frame_buffer[(8*i+8)+1+(64*charColumn)] = bar[forcast[index]*8+i];
    //     }  
    //     index++;
    // }
    char* dotw[14] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun", "Mon", "Tues", "Wed", "Thur", "Fri", "Sat"};
    int dayline = 2;
    int templine = 0;
    char* temp = malloc(sizeof(char)*16);
    switch (dispDay) {
        case 0:
            SSD1780_print2BufferLarge(dayline, dotw[clock_m->dotw+dispDay]);
            sprintf(temp, " %02i:%02i", tempLow[dispDay], tempHigh[dispDay]);
            SSD1780_print2Buffer(templine, temp);
            break;
        case 1:
            SSD1780_print2BufferLarge(dayline, dotw[clock_m->dotw+dispDay]);
            sprintf(temp, " %02i:%02i", tempLow[dispDay], tempHigh[dispDay]);
            SSD1780_print2Buffer(templine, temp);
            break;
        case 2:
            SSD1780_print2BufferLarge(dayline, dotw[clock_m->dotw+dispDay]);
            sprintf(temp, " %02i:%02i", tempLow[dispDay], tempHigh[dispDay]);
            SSD1780_print2Buffer(templine, temp);
            break;
        case 3:
            SSD1780_print2BufferLarge(dayline, dotw[clock_m->dotw+dispDay]);
            sprintf(temp, " %02i:%02i", tempLow[dispDay], tempHigh[dispDay]);
            SSD1780_print2Buffer(templine, temp);
            break;
        case 4:
            SSD1780_print2BufferLarge(dayline, dotw[clock_m->dotw+dispDay]);
            sprintf(temp, " %02i:%02i", tempLow[dispDay], tempHigh[dispDay]);
            SSD1780_print2Buffer(templine, temp);
            break;
        case 5:
            SSD1780_print2BufferLarge(dayline, dotw[clock_m->dotw+dispDay]);
            sprintf(temp, " %02i:%02i", tempLow[dispDay], tempHigh[dispDay]);
            SSD1780_print2Buffer(templine, temp);
            break;
        case 6:
            SSD1780_print2BufferLarge(dayline, dotw[clock_m->dotw+dispDay]);
            sprintf(temp, " %02i:%02i", tempLow[dispDay], tempHigh[dispDay]);
            SSD1780_print2Buffer(templine, temp);
            break;
    }
    SSD1780_displayBuffer();
}

void* inputThread() {
    int input;

    while (1) {
        input = getEncoderInput(3, 4, 5);
        // switching tabs
        if (input == 3) {
            if (cur_tab == MAX_TAB) {
                cur_tab = 0;
            } else {
                cur_tab++;                
            }
            // wait until not pressed
            while (getEncoderInput(3, 4, 5)) {
                Custom_wait(100);
            }
        }
        // changing day
        if (input == -1 && dispDay != 0 && cur_tab == 1) {
            dispDay--;
        } else if (input == 1 && dispDay != 6 && cur_tab == 1) {
            dispDay++;
        }
    }

}

int main() {   
    // Setup
    _i2c_init(1, i2c_node_address);
    SSD1780_defaultConfig();
    rtc_t* clock_m = initClock();

    pthread_create(&encoder, NULL, inputThread, NULL);

    while (1) {
        updateClock(clock_m);
        switch (cur_tab) {
            case (0):
                dispClock(clock_m);
                break;
            case (1):
                dispWeatherForcast(clock_m);
                break;
        }
    }

    _i2c_close();
    closeClock(clock_m);
    return 0;
}