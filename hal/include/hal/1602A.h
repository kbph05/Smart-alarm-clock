/**
 * @file 1602A.h
 * @brief The LCD module for the project. This module is responsible for handling inputs and outputs from the LCD screen, 
 * and communicating with app modules such as the clock, weather and calendar modules.
*/

#ifndef LCD_H
#define LCD_H

#include <gpiod.h>
#include <errno.h>
#include <string.h>

#define GPIOCHIP0 "/dev/gpiochip0";
#define GPIOCHIP1 "/dev/gpiochip1";
#define GPIOCHIP2 "/dev/gpiochip2";


/**
 * @brief Initializes the LCD module. Sets up the display and RTC. 
 * @param i Pointer to the interface structure.
 */
int LCD_init(struct interface *i);

/**
 * @brief Updates the display 
 * @return The next state of the state machine.
 */
void LCD_update();