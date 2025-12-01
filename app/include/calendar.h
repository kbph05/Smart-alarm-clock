/**
 * @file calendar.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-29
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#ifndef CALENDAR_H
#define CALENDAR_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

/**
 * @brief Holds data for each event. Summary is the title of the event, start_date 
 * is the start date of the event, and end_date is the end date of the event
 * 
 */
typedef struct {
    char summary[256];
    char start_date[20];
    char end_date[20];
} Event;

/**
 * @brief The calendar data struct. Contains an array of event structs and the number 
 * of elements in the events array
 * 
 */
typedef struct {
    int count;
    Event *events;
} CalendarData;

/**
 * @brief Initializes the calendar module by creating a new CalendarData struct and allocating memory for the events array
 * 
 * @return CalendarData* the struct to be used in the main loop
 */
CalendarData* initCalendar();

/**
 * @brief Grabs data from the calendar json file and stores it in the CalendarData struct
 * 
 * @return int the new state of the program
 */
int stateCalendar(CalendarData* data);

#endif