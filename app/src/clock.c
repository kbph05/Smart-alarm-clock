
#include "clock.h"
#include "stdint.h"


int initClock(struct interface *i) {

    return i->current_time;
}

int stateClock() {
    return 1;
}