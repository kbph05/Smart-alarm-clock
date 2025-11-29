/*
 * Based on ssd1306 linux driver
 */

#ifndef _i2c_H_
#define _i2c_H_

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <stdint.h>
#include <stdbool.h>

uint8_t _i2c_init(int i2c, int dev_addr);
uint8_t _i2c_close();
uint8_t _i2c_write(uint8_t* ptr, int16_t len);
uint8_t _i2c_read(uint8_t *ptr, int16_t len);

#endif