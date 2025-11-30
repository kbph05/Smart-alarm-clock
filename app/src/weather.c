#include "weather.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


WeatherData* initWeather() {
    WeatherData* data = malloc(sizeof(WeatherData));
    data->temps = malloc(sizeof(double) * 200);
    data->count = 0;
    return data;
}

int stateWeather(WeatherData* data) {
        
    FILE *f = fopen("/mnt/remote/myApps/json/weather.json", "r");
    char line[1024];
    // double temperatures[200];
    // int count = 0;

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
            double temp = 0;
            if (sscanf(line, " \"%*d\": %lf,", &temp) == 1) {
                if (data->count < 200) {
                    data->temps[data->count++] = temp;
                }
            }
        }
    }

    fclose(f);

    printf("Read %d hourly temperatures:\n", data->count);
    for (int i = 0; i < data->count; i++) {
        printf("Hour %d: %.2f °C\n", i, data->temps[i]);
    }

    return 3;
}