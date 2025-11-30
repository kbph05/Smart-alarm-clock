/**
 * @file weather.h
 * @brief the weather module for parsing the weather data from the OpenMeteo API
 * 
 */

#ifndef WEATHER_H
#define WEATHER_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/**
 * @brief The weather data struct. Contains an array of doubles for the temperatures and the number of elements in the array
 * 
 */
typedef struct {
    double *temps;
    int count;
} WeatherData;

/**
 * @brief Initializes the weather module by creating a new WeatherData struct and allocating memory for the temperatures array
 * 
 * @return WeatherData* the struct to be used in the main loop
 */
WeatherData* initWeather();

/**
 * @brief grabs the weather data from the JSON file and stores it in the WeatherData struct
 * 
 * @param data the struct used in the main loop
 * @return int the state of the program
 */
int stateWeather(WeatherData* data);

#endif