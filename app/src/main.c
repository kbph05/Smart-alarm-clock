
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
// uint8_t data_buf[1025];



void dispClock(rtc_t* time) {
    char* string = malloc(8*sizeof(char));
    sprintf(string, "%02i:%02i", time->hour, time->min);
    // memcpy(frame_buffer, interface_clock, 1024);
    SSD1780_print2BufferLarge(0, string);
    SSD1780_displayBuffer();
    free(string);
}

int main() {   
    // Setup
    _i2c_init(1, i2c_node_address);
    SSD1780_defaultConfig();

    // mains
    rtc_t* clock = initClock();
    WeatherData* weather = initWeather();       // weather struct
    CalendarData* calendar = initCalendar();    // calendar struct
    dispClock(clock);
    SSD1780_print2Buffer(3, "Good Morning!");

    SSD1780_displayBuffer();
    Custom_wait(2000);
    SSD1780_print2Buffer(3, "             ");
    SSD1780_print2Buffer(3, "Sat, Nov 29");
    SSD1780_displayBuffer();

    while (1) {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        clock->hour = tm.tm_hour;
        clock->min = tm.tm_min;
        dispClock(clock);

        // get weather
        int state = stateWeather(weather);
        Custom_wait(1000);

        // get calendar
        state = stateCalendar(calendar);
        Custom_wait(1000);
    }

    _i2c_close();
    closeClock(clock);
    return 0;
}