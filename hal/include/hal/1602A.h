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

typedef unsigned short uint16_t;

#define GPIOCHIP0 "/dev/gpiochip0"
#define GPIOCHIP1 "/dev/gpiochip1"
#define GPIOCHIP2 "/dev/gpiochip2"

unsigned int LINE_OFFSETS[] = {};          // Line offsets for 8 GPIO pins

struct gpiod_chip *chip;
struct gpiod_line_settings *settings;
struct gpiod_line_config *config;
struct gpiod_request_config *req_cfg;
struct gpiod_line_request *request;


/**
 * @brief Initializes the LCD module. Sets up the display and RTC. 
 * @param i Pointer to the interface structure.
 * @param CHIPNAME The name of the GPIO chip.
 * @return
 */
void initLCD(struct interface *i, const char *CHIPNAME);

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
uint16_t readLCD();

/**
 * @brief Updates the display with the pins to change
 * @param value The pin to change
 * @param value The value to change the pin to
 */
void updateLCD(int pin, int value);

#endif

