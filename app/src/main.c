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
const int MAX_TAB = 2;
int currTab = 0;
int currEvent = 0;
int dispDay = 0;
int calRotationT = 0;
int calRotationB = 0;
int calTimerT = 0;
int calTimerB = 0;
int maxEvents = 1;

char *weather_codes_m[] = {
    "clear-day",            // 0
    "rain",                 // 61, 63, 65, 56, 57, 
    "snow",
    "sleet",
    "wind",
    "fog",
    "cloudy",
    "partly-cloudy-day",
    "partly-cloudy-night"
};

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
    sprintf(dateString, "%s %s %02i %i", dotw[clock_m->dotw], month[clock_m->month], clock_m->day, clock_m->year);
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

void dispWeatherForcast(rtc_t* clock_m, WeatherData* WeatherData_m) {
    SSD1780_clearBuffer();
    // uint8_t forcast[7] = {1, 2, 3, 4, 5, 6, 7};
    // int index = 0;
    
    // int condition[7] = {1, 2, 3, 4, 5, 6, 7};
    // int tempHigh[7] = {11, 22, 33, 44, 55, 66, 77};
    // int tempLow[7] = {00, 11, 22, 33, 44, 55, 66};

    // for (int charColumn = 1; charColumn < 15; charColumn+=2) {
    //     for (int i = 1; i < 8; i++) { 
    //         if ((8*i+8)+1+(64*charColumn) > 1024) {
    //             break;
    //         }
    //         frame_buffer[(8*i+8)+1+(64*charColumn)] = bar[forcast[index]*8+i];
    //     }  
    //     index++;
    // }



    char* dotw[14] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    int dayline = 2;
    int condLine = 1;
    int templine = 0;
    char* meanTemp = malloc(sizeof(char)*32);
    char* weatherCondition = malloc(sizeof(char)*32);

    if (WeatherData_m->daily[dispDay].conditions == 0) {
        sprintf(weatherCondition, "          Clear");
    } else if (WeatherData_m->daily[dispDay].conditions == 45 || WeatherData_m->daily[dispDay].conditions == 48 || WeatherData_m->daily[dispDay].conditions == 1 || WeatherData_m->daily[dispDay].conditions == 2 || 
        WeatherData_m->daily[dispDay].conditions == 3) {
        sprintf(weatherCondition, "         Cloudy");
    } else if (WeatherData_m->daily[dispDay].conditions == 51 || WeatherData_m->daily[dispDay].conditions == 53 || WeatherData_m->daily[dispDay].conditions == 55 
        || WeatherData_m->daily[dispDay].conditions == 56 || WeatherData_m->daily[dispDay].conditions == 57 || WeatherData_m->daily[dispDay].conditions == 61 || WeatherData_m->daily[dispDay].conditions == 63 
        || WeatherData_m->daily[dispDay].conditions == 65 || WeatherData_m->daily[dispDay].conditions == 66 || WeatherData_m->daily[dispDay].conditions == 67 || WeatherData_m->daily[dispDay].conditions == 80 
        || WeatherData_m->daily[dispDay].conditions == 81 || WeatherData_m->daily[dispDay].conditions == 82) {
        sprintf(weatherCondition, "          Rainy");
    } else if (WeatherData_m->daily[dispDay].conditions == 71 || WeatherData_m->daily[dispDay].conditions == 73 || WeatherData_m->daily[dispDay].conditions == 75 || WeatherData_m->daily[dispDay].conditions == 77 || 
        WeatherData_m->daily[dispDay].conditions == 85 || WeatherData_m->daily[dispDay].conditions == 86) {
        sprintf(weatherCondition, "          Snowy");
    } else {
        sprintf(weatherCondition, "        Unknown");
    }


    sprintf(meanTemp, " %03.1fC   %03.1f:%03.1f", WeatherData_m->daily[dispDay].daily_temp, WeatherData_m->daily[dispDay].daily_min, WeatherData_m->daily[dispDay].daily_max);
    // sprintf(weatherCondition, "%s", weather_codes_m[(int)(WeatherData_m->daily->conditions)]);
    SSD1780_print2BufferLarge(dayline, dotw[clock_m->dotw+dispDay]);
    SSD1780_print2Buffer(condLine, weatherCondition);
    SSD1780_print2Buffer(templine, meanTemp);

    SSD1780_displayBuffer();
}

void dispCalendar(CalendarData* calendar_m) {
    SSD1780_clearBuffer();
    // char* line = malloc(sizeof(char)*256);
    // strncpy(line, calendar_m->events[0].summary, 15);
    // sprintf(line, "%s", calendar_m->events[0].summary);
    // SSD1780_print2Buffer(2, line);
    // char* line3 = malloc(sizeof(char)*16);
    // sprintf
    int eventTopMax = strlen(calendar_m->events[currEvent].summary) - 16;
    int eventBottomMax = strlen(calendar_m->events[currEvent+1].summary) - 16;

    if (calTimerT > 10) {
        calRotationT++;
    }
    if (calTimerB > 10) {
        calRotationB++;
    }

    if (calRotationT > eventTopMax && calTimerT > 0) {
        calTimerT = -10;
    }
    if (calRotationB > eventBottomMax && calTimerB > 0) {
        calTimerB = -10;
    }

    if (calTimerT == -1) {
        calRotationT = 0;
    }
    if (calTimerB == -1) {
        calRotationB = 0;
    }

    SSD1780_print2Buffer(3, calendar_m->events[currEvent].start_date);
    SSD1780_print2Buffer(2, calendar_m->events[currEvent].summary+calRotationT);
    SSD1780_print2Buffer(1, calendar_m->events[currEvent+1].start_date);
    SSD1780_print2Buffer(0, calendar_m->events[currEvent+1].summary+calRotationB);
    SSD1780_displayBuffer();

    Custom_wait(100);
    calTimerT++;
    calTimerB++;
}

void* inputThread() {
    int input;

    while (1) {
        input = getEncoderInput(3, 4, 5);
        // switching tabs
        if (input == 3) {
            if (currTab == MAX_TAB) {
                currTab = 0;
            } else {
                currTab++;                
            }
            // wait until not pressed
            while (getEncoderInput(3, 4, 5)) {
                Custom_wait(100);
            }
        }
        // changing day
        if (input == -1 && dispDay != 0 && currTab == 1) {
            dispDay--;
        } else if (input == 1 && dispDay != 6 && currTab == 1) {
            dispDay++;
        } else if (input == -1 && currEvent != 0 && currTab == 2) {
            currEvent--;
        } else if (input == 1 && (currEvent + 1) != maxEvents && currTab == 2) {
            currEvent++;
        }
    }

}

int main() {   
    // Setup
    _i2c_init(1, i2c_node_address);
    SSD1780_defaultConfig();



    rtc_t* clock_m = initClock();
    pthread_create(&encoder, NULL, inputThread, NULL);

    WeatherData* weather_m = initWeather();
    stateWeather(weather_m);

    CalendarData* calendar_m = initCalendar();
    stateCalendar(calendar_m);
    maxEvents = 10;//calendar_m->count;

    while (1) {
        updateClock(clock_m);
        dispWeatherForcast(clock_m, weather_m);
        // switch (currTab) {
        //     case (0):
        //         dispClock(clock_m);
        //         break;
        //     case (1):
        //         dispWeatherForcast(clock_m, weather_m);
        //         break;
        //     case (2):
        //         dispCalendar(calendar_m);
        //         break;
        // }
    }

    _i2c_close();
    closeClock(clock_m);
    return 0;
}