// #include "HAL/1602A.h"
// #include "HAL/encoder.h"
// #include "HAL/neopixel.h"

// #include "calendar.h"
// #include "weather.h"
// #include "clock.h"
// #include "interface.h"

// States
#define EXIT -1
#define INITIALIZATION 0
#define CLOCK 1
#define WEATHER 2
#define SETTINGS 3

// Types (later replaced by stdlib)
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef long long int uint64_t;

// Vars
struct interface {
    uint64_t current_time;
    uint16_t current_weather;
    char* current_location[64];
    uint16_t ui_tape[8];
};

// uint8_t ip[4];

int state = INITIALIZATION;

void main() { 
    while (1) {
        switch (state) {
            case INITIALIZATION:
                struct interface* interface_p = initInterface();
                initLocation(interface_p);
                initClock(interface_p);
                initWeather(interface_p);
                state = CLOCK;
                break;
            case CLOCK:
                state = stateClock();
                break;
            case WEATHER:
                state = stateWeather();
                break;
            case SETTINGS:
                state = stateSettings();
                break;
            case EXIT:
                exit(0);
                break;
            default:
                perror("State out of bound, exiting");
                exit(-1);
        }
    }
}