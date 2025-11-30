/**
 * @file weather.js
 * @brief The weather module for the project. This module is responsible
 * for getting the 7 day forcast weather data from the OpenMeteo API.
 */


import { fetchWeatherApi } from "openmeteo";
import * as fs from 'fs';

export async function getIP() {
    try {
        const response = await fetch('http://ip-api.com/json/');
        if (!response.ok) {
            throw new Error(`HTTP error: ${response.status}`);
        }
        const data = await response.json(); 
        const ip = {
            latitude: data.lat,
            longitude: data.lon
        }
        console.log("lat, long: %d, %d", data.lat, data.lon);
        return ip;

    } catch (error) {
        console.error("Error fetching latitude/longitude:", error);
        return null;
    }
    
}


// Credits from openmeteo for the template
export async function getWeatherAPI(lat, lon) {
    const params = {
        latitude: lat,
        longitude: lon,
        daily: ["temperature_2m_mean", "weather_code"],
        hourly: "temperature_2m"
    };
   const url = "https://api.open-meteo.com/v1/forecast";
   
    try {                     
        const responses = await fetchWeatherApi(url, params);
        const response = responses[0];
        const hourly = response.hourly();
        const daily = response.daily();
        const utcOffsetSeconds = response.utcOffsetSeconds();

        const weatherData = {
            hourly: {
                time: Array.from({ length: (Number(hourly.timeEnd()) - Number(hourly.time())) / hourly.interval() }, 
                    (_, i) => new Date((Number(hourly.time()) + i * hourly.interval() + utcOffsetSeconds) * 1000)
                ),
                temperature: hourly.variables(0).valuesArray(),
            },
            daily: {
                time: Array.from(
                    { length: (Number(daily.timeEnd()) - Number(daily.time())) / daily.interval() }, 
                    (_, i) => new Date((Number(daily.time()) + i * daily.interval() + utcOffsetSeconds) * 1000)
                ),
                temperature_mean: daily.variables(0).valuesArray(),
                weather_code: daily.variables(1).valuesArray(),
            },
        };
        return weatherData;
    } catch (error) {
        console.error("Error fetching weather data:", error);
        return null;
    }

}


export function weatherJSON(data) {
    try {
        const json = JSON.stringify(data, null, 2);
        fs.writeFileSync('/home/kbph/ENSC_351/public/myApps/weather.json', json);
    }
    catch (error) {
        console.error("Error writing to JSON file:", error);
        return null;
    }
}

// Weather code table:
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