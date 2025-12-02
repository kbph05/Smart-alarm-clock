/**
 * @file weather.h
 * @brief the weather module for parsing the weather data from the OpenMeteo API
 * 
 */


// Weather code table (according to the openmeteo website)
/**
 * Code	            Description
    0	             Clear sky
    1, 2, 3	         Mainly clear, partly cloudy, and overcast
    45, 48	         Fog and depositing rime fog
    51, 53, 55	     Drizzle: Light, moderate, and dense intensity
    56, 57	         Freezing Drizzle: Light and dense intensity
    61, 63, 65	     Rain: Slight, moderate and heavy intensity
    66, 67	         Freezing Rain: Light and heavy intensity
    71, 73, 75	     Snow fall: Slight, moderate, and heavy intensity
    77	             Snow grains
    80, 81, 82	     Rain showers: Slight, moderate, and violent
    85, 86	         Snow showers slight and heavy
    95 *	         Thunderstorm: Slight or moderate
    96, 99 *	     Thunderstorm with slight and heavy hail
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
    double daily_temp;
    double conditions;
    double daily_max;
    double daily_min;
} Daily;

typedef struct {
    Daily *daily;
    int daily_count;
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