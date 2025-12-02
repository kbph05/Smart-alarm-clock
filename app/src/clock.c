
#include "clock.h"
#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "time.h"

rtc_t* initClock() {
    rtc_t *clock_m = malloc(sizeof(rtc_t));
    clock_m->hour = 0;
    clock_m->min = 0; 
    clock_m->day = 0;
    clock_m->month = 0;
    clock_m->year = 0;
    clock_m->isPm = 0;
    clock_m->dotw = 0;
    return clock_m;
}

void updateClock(rtc_t* clock_m) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    clock_m->hour = tm.tm_hour;
    clock_m->min = tm.tm_min;
    clock_m->day = tm.tm_mday;
    clock_m->month = tm.tm_mon;
    clock_m->year = tm.tm_year + 1900;
    clock_m->isPm = 0;
    clock_m->dotw = tm.tm_wday;

    if (clock_m->hour > 12) {
        clock_m->hour -= 12;
        clock_m->isPm = 1;
    }
}
void closeClock(rtc_t* clock) {
    free(clock);
}

int stateClock() {
    return 1;
}