
#include "clock.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"

rtc_t* initClock() {
    rtc_t *clock = malloc(sizeof(rtc_t));
    clock->hour = 0;
    clock->min = 0; 
    clock->month = 0;
    clock->day = 0;
    clock->dotw = 0;
    clock->year = 0;
    clock->isPm = 0;
    return clock;
}

void closeClock(rtc_t* clock) {
    free(clock);
}

int stateClock() {
    return 1;
}