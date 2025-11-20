/**
 * @file time.js
 * @brief The time module for the project. This module is responsible for getting the current time
 * from the IP API, or as a backup, the RTC on the Beagle-YAI. It writes the time to the time.json file.
 * 
 * Currently it graps the time in 12 hour format, however if we want to include AM/PM, we will need to 
 * change it back to 24 hour format.
 * 
 */

const { time } = require('console');
const { parse } = require('path');


// ------ Get the time using IP API to fetch timezone ------
async function getAPI() {
    try {
        const response = await fetch('http://ip-api.com/json/');
        if (!response.ok) {
            throw new Error(`HTTP error - status: ${response.status}`);
        }
        const data = await response.json();
        const now = new Date().toLocaleTimeString('en-US', {timeZone: data.timezone, hour12: false, dst: true});

        const timeAPI = {
            h : ((now.split(':')[0] > 12) ? now.split(':')[0] - 12 : now.split(':')[0]).toString(),
            m : now.split(':')[1],
            s : now.split(':')[2],
        }
        
        console.log(timeAPI);
        return timeAPI;
    } catch (error) {
        console.error("Error fetching timezone:", error);
        return null;
    }

}

// ------ Fallback: Gets the RTC from the target ------
function getRTC() {

    const now = new Date();

    let hours = now.getHours() - 12;
    let minutes = now.getMinutes();
    let seconds = now.getSeconds();

    const format = (num) => num < 10 ? `0${num}` : num.toString(); // formating for seconds and minutes when > 10

    const timeRTC = {
        h : ((now.getHours() > 12) ? now.getHours() - 12 : now.getHours()).toString(),
        m : format(now.getMinutes()),
        s : format(now.getSeconds())
    }

    console.log(`Current Time: ${hours}:${format(minutes)}:${format(seconds)}`);

    return timeRTC;
}

// ------ Writes the time to a JSON file ------
async function parseJSON(t) {
    try {
        const fs = require('fs');
        const json = JSON.stringify(t, null, 2);
        console.log(json);
        fs.writeFileSync('time.json', json);
    }
    catch (error) {
        console.error("Error writing to JSON file:", error);
        return null;
    }
}

module.exports = {
    getRTC,
    getAPI,
    parseJSON
};