// main file 


import { getAPI } from './time.js';
import { getRTC } from './time.js';
import { parseJSON } from './time.js';
import { getWeatherAPI } from './weather.js';
import { weatherJSON } from './weather.js';
import { getIP } from './weather.js';

async function time() {
    try {
        time = await getAPI();
        parseJSON(time);
    } catch (error) {
        console.error("Error fetching timezone:", error, "Using fallback RTC");
        time = await getRTC();
        parseJSON(time);
    }
}

async function weather() {
    try {
        const ip = await getIP();
        const weather = await getWeatherAPI(ip.latitude, ip.longitude);
        weatherJSON(weather);
    } catch (error) {
        console.error("Error fetching weather data:", error);
        return null;
    }
}

time();
weather();