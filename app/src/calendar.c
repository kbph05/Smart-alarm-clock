

#include "calendar.h"
#include <stdio.h>
#include <time.h>
#include <string.h>


typedef struct {
    char summary[256];
    char start_date[20];
} Event;


void Calendar_init() {
    return;
}



int stateCalendar() {
    
    FILE* file = fopen("/mnt/remote/myApps/calendar.json", "r");
    if (!file) {
        perror("Failed to open calendar.json");
        return -1;
    }

    Event events[500];
    int count = 0;
    char line[1024];
    int in_event = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "\"kind\": \"calendar#event\"")) {
            in_event = 1;
            events[count].summary[0] = '\0';
            events[count].start_date[0] = '\0';
        }

        if (in_event) {
            char *s = strstr(line, "\"summary\":");
            if (s) {
                s += strlen("\"summary\":");
                while (*s == ' ' || *s == '\"') s++;
                char *end = strchr(s, '\"');
                if (end) *end = '\0';
                strcpy(events[count].summary, s);
            }
            s = strstr(line, "\"date\":");
            if (s) {
                s += strlen("\"date\":");
                while (*s == ' ' || *s == '\"') s++;
                char *end = strchr(s, '\"');
                if (end) *end = '\0';
                strcpy(events[count].start_date, s);
            }

            if (strstr(line, "},")) {
                count++;
                in_event = 0;
            }
        }
    }

    fclose(file);

    printf("All events:\n");
    for (int i = 0; i < count; i++) {
        printf("%s\n", events[i].summary);
    }

    return 1;


}