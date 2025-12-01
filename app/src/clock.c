
#include "clock.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"

rtc_t* initClock() {
    rtc_t *clock = malloc(sizeof(rtc_t));
    clock->hour = 0;
    clock->min = 0; 
    return clock;
}

rtc_t* initClock() {
    rtc_t *clock = malloc(sizeof(rtc_t));
    clock->hour = 0;
    clock->min = 0; 
    return clock;
}

void closeClock(rtc_t* clock) {
    free(clock);
}

int stateClock() {
    return 1;
}