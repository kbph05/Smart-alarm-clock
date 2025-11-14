/**
 * @file encoder.h
 * @brief The encoder module for the project. This module is responsible for handling inputs and
 * outputs from the encoder, which will control the display.
 */

#ifndef ENCODER_H
#define ENCODER_H

//#include <gpiod.h>
#include <errno.h>
#include <string.h>

#define GPIOCHIP1 "/dev/gpiochip1"

unsigned int LINE_OFFSETS[] = {33, 41};

struct gpiod_chip *chip;
struct gpiod_chip *chip;
struct gpiod_line_settings *settings;
struct gpiod_line_config *config;
struct gpiod_request_config *req_cfg;
struct gpiod_line_request *request;

#include <errno.h>
#include <string.h>

/**
 * @brief Initializes the encoder module by reading the GPIO pins
 * @param i Pointer to the interface structure.
 */
void initEncoder();

/**
 * @brief Gets the encoder values from the GPIO pins.
 * @return An array of values of the encoder pins.
 */
int* readEncoder();

/**
 * @brief closes the chip and frees memory
 */
void cleanEncoder();

#endif