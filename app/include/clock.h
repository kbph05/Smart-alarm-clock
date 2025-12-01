/**
 * @file clock.h
 * @brief The clock module for the project. This module is responsible for updating the display
 * with the current time every second.
 * It also uses the RTC on the Beagle-YAI to get the current time. 
*/

#include <stdlib.h>
#include <stdint.h>

#ifndef CLOCK_H
#define CLOCK_H

typedef struct {
    int hour;
    int min;
    int day;
    int month;
    int year;
    int dotw; //day of the week
    int isPm;
} rtc_t;

/**
 * @brief Initializes the clock module. 
 * @return Clock type structure.
 */
rtc_t* initClock();

/**
 * @brief Closes the clock module, freeing memory. 
 * @param Clock type structure.
 */
void closeClock(rtc_t* clock);

/**
 * @brief Updates the display with the current time. 
 * @return The next state of the state machine.
 */
int stateClock();
#endif