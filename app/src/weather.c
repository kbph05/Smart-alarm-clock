#include "weather.h"

char *weather_codes[] = {
    "clear-day",            // 0
    "rain",                 // 61, 63, 65, 56, 57, 
    "snow",
    "sleet",
    "wind",
    "fog",
    "cloudy",
    "partly-cloudy-day",
    "partly-cloudy-night"
};

// void getWeatherCode(int code) {
//     switch (code) {
//         case 0:
//             printf("Clear day");
//             break;
//         default: 
//             printf("Unknown code");
//             break;       
//     }
// }

WeatherData* initWeather() {
    WeatherData* data = malloc(sizeof(WeatherData));
    data->count = 0;
    data->daily_count = 0;
    data->daily = malloc(sizeof(Daily) * 200);
    return data;
}

int stateWeather(WeatherData* data) {
        
    FILE *f = fopen("/mnt/remote/myApps/json/weather.json", "r");
    char line[1024];

    // int in_temperature_block = 0; // unused 
    int in_daily_temp_block = 0;
    int in_weather_code_block = 0;
    int temp_index = 0;
    int max_index = 0;
    int min_index = 0;
    int in_daily_max_block = 0;
    int in_daily_min_block = 0;

    
    while (fgets(line, sizeof(line), f)) {

        // Daily temperatures
        if (strstr(line, "\"temperature_mean\"")) {
            in_daily_temp_block = 1;
        }
        if (in_daily_temp_block && strstr(line, "}")) {
            in_daily_temp_block = 0;
        }
        if (in_daily_temp_block) {
            double daily_temp = 0;
            if (sscanf(line, " \"%*d\": %lf,", &daily_temp) == 1) {
                if (temp_index < 7) {
                    data->daily[temp_index++].daily_temp = daily_temp;
                }
            }
        }

        if (strstr(line, "\"temperature_2m_max\"")) {
            in_daily_max_block = 1;
        }
        if (in_daily_max_block && strstr(line, "}")) {
            in_daily_max_block = 0;
        }
        if (in_daily_max_block) {
            double daily_max = 0;
            if (sscanf(line, " \"%*d\": %lf,", &daily_max) == 1) {
                if (max_index < 7) {
                    data->daily[max_index++].daily_max = daily_max;
                }
            }
        }

        if (strstr(line, "\"temperature_2m_min\"")) {
            in_daily_min_block = 1;
        }
        if (in_daily_min_block && strstr(line, "}")) {
            in_daily_min_block = 0;
        }
        if (in_daily_min_block) {
            double daily_min = 0;
            if (sscanf(line, " \"%*d\": %lf,", &daily_min) == 1) {
                if (min_index < 7) {
                    data->daily[min_index++].daily_min = daily_min;
                }
            }
        }
        

        // Conditions 
        if (strstr(line, "\"weather_code\"")) {
            in_weather_code_block = 1;
        }
        if (in_weather_code_block && strstr(line, "}")) {
            in_weather_code_block = 0;
        }
        if (in_weather_code_block) {
            printf("%s\n", "inside weather code block");
            int code = 0;
            if (sscanf(line, " \"%*d\": %d,", &code) == 1) {
                if (data->count < 7) {
                    data->daily[data->count++].conditions = code;
                }
            }
        }


        
    }

    fclose(f);

    printf("\nDaily mean temperatures and Conditions:\n");
    int k = 1;
    for (int i = 0; i < data->count; i++) {
        printf("Day %i: %.2f °C, Max: %.2f °C, Min: %.2f °C, code %.2f\n", k, data->daily[i].daily_temp, data->daily[i].daily_max, data->daily[i].daily_min, data->daily[i].conditions);
        k++;
    }

    return 3;
}