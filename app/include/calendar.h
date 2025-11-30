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

typedef struct {
    char summary[256];
    char start_date[20];
    char end_date[20];
} Event;

typedef struct {
    int *days;
    int count;
    Event *events;
} CalendarData;

CalendarData* initCalendar();
int stateCalendar();

#endif