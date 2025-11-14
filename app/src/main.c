#include "HAL/1602A.h"
#include "HAL/encoder.h"
// #include "HAL/neopixel.h"

// #include "calendar.h"
// #include "weather.h"
#include "clock.h"
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

void initInterface(struct interface* interface_p) {
    Location_init(interface_p);
    initClock(interface_p);
    Weather_init(interface_p);
}

void updateTape(struct interface* interface_p) {
    for (int j = 0; j < 8; j++) {
        interface_p->ui_tape[j] = readLCD(j);
    }
}

void main() { 
    struct interface* interface_p = malloc(sizeof(struct interface));
    while (1) {
        switch (state) {
            case INITIALIZATION:
                // struct interface* interface_p;
                if (interface_p != NULL) {
                    initInterface(interface_p);
                }
                //initInterface(interface_p);
                break;
            case CLOCK:
                state = stateClock();
                updateTape(interface_p);
                break;
            case WEATHER:
                state = stateWeather();
                break;
            case SETTINGS:
                state = stateSettings();
                break;
            case EXIT:
                free(interface_p);
                exit(0);
                break;
            default:
                perror("State out of bound, exiting");
                exit(-1);
        }
    }
}