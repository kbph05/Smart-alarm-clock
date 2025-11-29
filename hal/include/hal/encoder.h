/**
 * @file encoder.h
 * @brief The encoder module for the project. This module is responsible for handling inputs and
 * outputs from the encoder, which will control the display.
 */

#ifndef ENCODER_H
#define ENCODER_H

#include "spi.h"
#include "hal/customWait.h"
#include "stdint.h"




// Returns direction of the encoder
// -1: left, 0: NULL, 1: right
int getEncoderInput();

#endif