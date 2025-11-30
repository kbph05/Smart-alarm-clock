// main file 


import { getAPI } from './time.js';
import { getRTC } from './time.js';
import { parseJSON } from './time.js';
import { checkIfCalendarIsFetched } from './calendar.js';
import { checkIfWeatherIsFetched } from './weather.js';
import fetch from 'node-fetch';

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

async function main() {

    // await time();
    await checkIfCalendarIsFetched();
    await checkIfWeatherIsFetched();
    setInterval(checkIfWeatherIsFetched, 24 * 60 * 60 * 1000); // check every day
    setInterval(checkIfCalendarIsFetched, 24 *60 * 60 * 1000);  // check every day
}

main();