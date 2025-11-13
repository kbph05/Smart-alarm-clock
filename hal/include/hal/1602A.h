/**
 * @file 1602A.h
 * @brief The LCD module for the project. This module is responsible for handling inputs and outputs from the LCD screen, 
 * and communicating with app modules such as the clock, weather and calendar modules.
*/

#ifndef _1602A_H_
#define _1602A_H_

//#include <gpiod.h>
#include <errno.h>
#include <string.h>

#define GPIOCHIP0 "/dev/gpiochip0"
#define GPIOCHIP1 "/dev/gpiochip1"
#define GPIOCHIP2 "/dev/gpiochip2"


/**
 * @brief Initializes the LCD module. Sets up the display and RTC. 
 * @param i Pointer to the interface structure.
 * @param CHIPNAME The name of the GPIO chip.
 * @return The initialization status.
 */
int initLCD(struct interface *i, const char *CHIPNAME);
/**
 * @brief Updates the display 
 * @return The next state of the state machine.
 */
void updateLCD();

/**
 * @brief Cleans up the LCD module at the end of the program and if an error occurs
 */
void cleanLCD();

/**
 * @brief Reads the current state of the LCD module
 * @return The values of the pins on the LCD
 */
int* readLCD();

/**
 * @brief Updates the display with the pins to change
 * @param value The pin to change
 * @param value The value to change the pin to
 */
void updateLCD(int pin, int value);

#endif

