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
        hourly: "temperature_2m",
    };
   const url = "https://api.open-meteo.com/v1/forecast";
   
    try {                     
        const responses = await fetchWeatherApi(url, params);
        const response = responses[0];
        const hourly = response.hourly();
        const utcOffsetSeconds = response.utcOffsetSeconds();

        const weatherData = {
            hourly: {
                time: Array.from({ length: (Number(hourly.timeEnd()) - Number(hourly.time())) / hourly.interval() }, 
                    (_, i) => new Date((Number(hourly.time()) + i * hourly.interval() + utcOffsetSeconds) * 1000)
                ),
                temperature: hourly.variables(0).valuesArray(),
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
        fs.writeFileSync('weather.json', json);
    }
    catch (error) {
        console.error("Error writing to JSON file:", error);
        return null;
    }
}