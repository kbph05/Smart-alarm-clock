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


export async function getCalendar() {
    
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

export async function calendarJSON(data) {
    try {
        const json = JSON.stringify(data, null, 2);
        fs.writeFileSync('calendar.json', json);
    }
    catch (error) {
        console.error("Error writing to JSON file:", error);
        return null;
    }
}