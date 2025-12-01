/**
 * @file weather.js
 * @brief The weather module for the project. This module is responsible
 * for getting the 7 day forcast weather data from the OpenMeteo API.
 */


import { fetchWeatherApi } from "openmeteo";
import * as fs from 'fs';
import { loadCache, saveCache } from './cache.js';
const cache = loadCache();

function isToday(timestamp) {
    if (!timestamp) return false;
    const last = new Date(timestamp);
    const now = new Date();
    return last.toDateString() === now.toDateString();
}

async function getIP() {
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

// Credits to openmeteo for the template
async function getWeatherAPI(lat, lon) {
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


function weatherJSON(data) {
    try {
        const json = JSON.stringify(data, null, 2);
        fs.writeFileSync('/home/kbph/ENSC_351/public/myApps/json/weather.json', json);
    }
    catch (error) {
        console.error("Error writing to JSON file:", error);
        return null;
    }
}



export async function checkIfWeatherIsFetched() {
    if (isToday(cache.lastWeatherFetch)) {
        console.log("Weather already fetched today.");
        return;
    }

    try {
        const ip = await getIP();
        const weather = await getWeatherAPI(ip.latitude, ip.longitude);
        weatherJSON(weather);

        cache.lastWeatherFetch = new Date().toISOString();
        saveCache(cache);

        console.log("Weather fetched.");
    } catch (e) {
        console.error("Weather fetch failed:", e);
    }
}