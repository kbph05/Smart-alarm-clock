/**
 * @file weather.h
 * @brief the weather module for parsing the weather data from the OpenMeteo API
 * 
 */

#ifndef WEATHER_H
#define WEATHER_H

#include <stdlib.h>
#include <stdint.h>

void Weather_init(uint16_t *current_weather);
int stateWeather();

#endif