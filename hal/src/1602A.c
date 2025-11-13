#define _GNU_SOURCE

#include "hal/1602A.h"

unsigned int LINE_OFFSETS[] = {33, 41};

struct gpiod_chip *chip;
struct gpiod_line_settings *settings;
struct gpiod_line_config *config;
struct gpiod_request_config *req_cfg;
struct gpiod_line_request *request;

int initLCD(struct interface *i, const char *CHIPNAME) {
    chip = NULL;
    settings = NULL;
    config = NULL;
    req_cfg = NULL;
    request = NULL;

    // 1. open the gpiochip
    chip = gpiod_chip_open(CHIPNAME);
    if (chip == NULL){
        printf("%s", "[1602A] Cannot open the chip\n");
        goto error;
    }
    printf("%s", "[1602A] Chip opened\n");


   // 2. Create line settings (INPUT for encoder signals)
    settings = gpiod_line_settings_new();
    if (!settings){
        printf("%s", "[1602A] Cannot get line settings");
        goto error;
    }

    // 3. Create line config and request the line
    config = gpiod_line_config_new();
    if (!config){
        printf("%s", "[1602A] Cannot get line config");
        goto error;
    }
    gpiod_line_config_add_line_settings(config, LINE_OFFSETS, 8, settings);


    // 4. Create request config
    req_cfg = gpiod_request_config_new();
    if (!req_cfg){
        printf("%s", "[1602A] Cannot get request config");
        goto error;
    }
    gpiod_request_config_set_consumer(req_cfg, "myapp");


    // 5. Request the lines
    request = gpiod_chip_request_lines(chip, req_cfg, config);
    if (!request){
        printf("%s", "[1602A] Cannot get request");
        goto error;
    }

printf("[1602A] Encoder initialized on GPIOs %u, %u, %u, %u, %u, %u, %u, %u\n", LINE_OFFSETS[0], LINE_OFFSETS[1], LINE_OFFSETS[2], LINE_OFFSETS[3], LINE_OFFSETS[4], LINE_OFFSETS[5], LINE_OFFSETS[6], LINE_OFFSETS[7]);
    return;

    error:
        clean_encoder(); // cleans only what’s been allocated so far
        return;
}

int* readLCD() {
    if (!request) return -1;

    int values[8];
    int ret = gpiod_line_request_get_values(request, values);
    if (ret < 0) {
        printf("[1602A] Failed to read encoder lines: %s\n", strerror(errno));
        return -1;
    }
    return values;
}

void cleanLCD() {

    printf("clean_encoder() called — closing GPIO chip now\n");

    if (request != NULL) {
        gpiod_line_request_release(request);
        request = NULL;
    }
    if (req_cfg != NULL) {
        gpiod_request_config_free(req_cfg);
        req_cfg = NULL;
    }
    if (config != NULL) {
        gpiod_line_config_free(config);
        config = NULL;
    }
    if (settings != NULL) {
        gpiod_line_settings_free(settings);
        settings = NULL;
    }
    if (chip != NULL) {
        gpiod_chip_close(chip);
        chip = NULL;
    }
    return;
}

void updateLCD(int pin, int value) {

    int ret = gpiod_line_request_set_values(request, value);
    if (ret < 0) {
        printf("[1602A] Failed to set encoder lines: %s\n", strerror(errno));
        return;
    }
    return;

}