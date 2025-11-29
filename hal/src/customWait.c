#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "hal/customWait.h"

#define MS_IN_SECOND 1000

void Custom_wait(int time_ms) {
    clock_t timeStart;
    timeStart = clock();
    float timeElapsed = 0;
    while ( timeElapsed <= time_ms) {
       timeElapsed = (float)((clock() - timeStart)/(CLOCKS_PER_SEC/MS_IN_SECOND));
    }
}
void Custom_randWait(int time_msL, int time_msU) {
    int time_ms = rand() % (time_msU - time_msL);

    clock_t timeStart;
    timeStart = clock();
    float timeElapsed = 0;
    while ( timeElapsed <= time_ms) {
       timeElapsed = (float)((clock() - timeStart)/(CLOCKS_PER_SEC/MS_IN_SECOND));
    }
}