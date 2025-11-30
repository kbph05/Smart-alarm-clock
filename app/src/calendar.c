

#include "calendar.h"
#include <stdio.h>
#include <time.h>
#include <string.h>


CalendarData* initCalendar() {
    CalendarData* data = malloc(sizeof(CalendarData));
    data->days = NULL;
    data->count = 0;
    data->events = malloc(sizeof(Event) * 500);
    return data;
}

int stateCalendar(CalendarData* data) {
    
    FILE* file = fopen("/mnt/remote/myApps/json/calendar.json", "r");       // replace this with the path to the json files directory
    if (!file) {
        perror("Failed to open calendar.json");
        return -1;
    }

    Event events[500];
    char line[1024];
    int in_event = 0;
    int in_start = 0;
    int in_end = 0;


    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "\"kind\": \"calendar#event\"")) {
            in_event = 1;
            data->events[data->count].summary[0] = '\0';
            data->events[data->count].start_date[0] = '\0';
        }

        if (!in_event) { continue; }

        // Summary of the event
        char *s = strstr(line, "\"summary\":");
        if (s) {
            // s += strlen("\"summary\":");
            s = strchr(s, ':') + 1;
            while (*s == ' ' || *s == '\"') s++;
            char *end = strchr(s, '\"');
            if (end) *end = '\0';
            strcpy(data->events[data->count].summary, s);
            continue;
        }

        // if (strstr(line, "start")) {
        //     for (int i = 0; line[i]; i++) printf("%02X ", (unsigned char)line[i]);
        //     printf("\n");
        // }

        // Start date
        if (strstr(line, "\"start\":")) {
            in_start = 1;
            continue;    // go to next line
        }
        if (in_start && strstr(line, "\"date\"")) {
            s = strchr(strstr(line, "\"date\""), ':');
            if (s) {
                s++;
                while (*s == ' ' || *s == '\"') s++;
                char *end = strchr(s, '\"');
                if (end) *end = '\0';
                strcpy(data->events[data->count].start_date, s);
            }
            in_start = 0;
            continue;
        }

        // End date
        if (strstr(line, "\"end\":")) {
            in_end = 1;
            continue;
        }
        if (in_end && strstr(line, "\"date\"")) {
            s = strchr(strstr(line, "\"date\""), ':');
            // s = strchr(s, ':');
            if (s) {
                s++;
                while (*s == ' ' || *s == '\"') s++;
                char *end = strchr(s, '\"');
                if (end) *end = '\0';
                strcpy(data->events[data->count].end_date, s);
            }
            in_end = 0;
            continue;
        }

        if (!in_start && strstr(line, "\"transparency\":")) {
            data->count++;
            in_event = 0;
            in_start = 0;
        }
        
    }

    fclose(file);

    printf("All events:\n");
    for (int i = 0; i < data->count; i++) {
        printf("%s - Start: %s End: %s\n\n", data->events[i].summary, data->events[i].start_date, data->events[i].end_date);
    }

    return 1;


}