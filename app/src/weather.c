#include "weather.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void Weather_init(uint16_t *current_weather) {
    printf("weather init %d\n", *current_weather);
    return;
}

int stateWeather() {
        
    FILE *f = fopen("/mnt/remote/myApps/weather.json", "r");
    char line[1024];
    double temperatures[200];
    int count = 0;

    int in_temperature_block = 0;

    
    while (fgets(line, sizeof(line), f)) {
        if (strstr(line, "\"temperature\"")) {
            in_temperature_block = 1;
            continue;
        }
        if (in_temperature_block && strstr(line, "}")) {
            break;
        }
        if (in_temperature_block) {
            double temp;
            if (sscanf(line, " \"%*d\": %lf,", &temp) == 1) {
                temperatures[count++] = temp;
            }
        }
    }

    fclose(f);

    printf("Read %d hourly temperatures:\n", count);
    for (int i = 0; i < count; i++) {
        printf("Hour %d: %.2f °C\n", i, temperatures[i]);
    }

    return 3;
}