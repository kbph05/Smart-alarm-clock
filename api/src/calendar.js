/**
 * @file calendar.js
 * @brief The calendar module for the project. This module is responsible for fetching the google calendar based on
 * the user's credentials. It writes each calendar event to a json file.
 * 
 * (side note: it only fetches events from my calendar because it has my credentials)
 */


import path from 'node:path';
import process from 'node:process';
import {authenticate} from '@google-cloud/local-auth';
import {google} from 'googleapis';
import * as fs from 'fs';
import { loadCache, saveCache } from './cache.js';
const cache = loadCache();

function isToday(timestamp) {
    if (!timestamp) return false;
    const last = new Date(timestamp);
    const now = new Date();
    return last.toDateString() === now.toDateString();
}


async function getCalendar() {
    
    const SCOPES = ['https://www.googleapis.com/auth/calendar.readonly'];
    const CREDENTIALS_PATH = path.join(process.cwd(), 'credentials.json');
    try {
        const auth = await authenticate({
            scopes: SCOPES,
            keyfilePath: CREDENTIALS_PATH,
        });
        const calendar = google.calendar({version: 'v3', auth});
        const calendarId = await calendar.calendarList.list();
        const calendarData = await calendar.events.list({
            calendarId: calendarId.data.items[0].id,
            timeMin: new Date().toISOString(),
            maxResults: 20,
            singleEvents: true,
            orderBy: 'startTime',
        });
        const events = calendarData.data.items;
        return events;
    }
    catch (error) {
        console.error("Error fetching Google calendar data:", error);
        return null;
    }
    
}

async function calendarJSON(data) {
    try {
        const json = JSON.stringify(data, null, 2);
        fs.writeFileSync('/home/kbph/ENSC_351/public/myApps/json/calendar.json', json);
    }
    catch (error) {
        console.error("Error writing to JSON file:", error);
        return null;
    }
}


export async function checkIfCalendarIsFetched() {
    if (isToday(cache.lastCalendarFetch)) {
        console.log("Calendar already fetched today.");
        return;
    }

    try {
        const cal = await getCalendar();
        calendarJSON(cal);

        cache.lastCalendarFetch = new Date().toISOString();
        saveCache(cache);

        console.log("Calendar fetched.");
    } catch (e) {
        console.error("Calendar fetch failed:", e);
    }
}