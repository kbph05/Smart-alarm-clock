/**
 * @file weather.h
 * @brief the weather module for parsing the weather data from the OpenMeteo API
 * 
 */

#ifndef WEATHER_H
#define WEATHER_H

#include <stdlib.h>
#include <stdint.h>


typedef struct {
    double *temps;
    int count;
} WeatherData;


WeatherData* initWeather();
int stateWeather(WeatherData* data);

#endif