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

extern struct interface;

/**
 * @brief Initializes the clock module. Sets up the display and RTC. 
 * @param i Pointer to the interface structure.
 */
int initClock(struct interface *i);

/**
 * @brief Updates the display with the current time. 
 * @return The next state of the state machine.
 */
int stateClock();
#endif