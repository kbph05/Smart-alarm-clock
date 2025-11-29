#ifndef __SSD1780_H__
#define __SSD1780_H__

#include <stdbool.h>

#define SSD1780_MAX_WIDTH 128
#define SSD1780_MAX_HEIGHT 64

#define SSD1780_I2C_ADDR            0x3c

#define SSD1780_COMM_CONTROL_BYTE   0x00
#define SSD1780_DATA_CONTROL_BYTE   0x40

#define SSD1780_COMM_DISPLAY_OFF    0xae
#define SSD1780_COMM_DISPLAY_ON     0xaf
#define SSD1780_COMM_HORIZ_NORM     0xa0
#define SSD1780_COMM_HORIZ_FLIP     0xa1
#define SSD1780_COMM_RESUME_RAM     0xa4
#define SSD1780_COMM_IGNORE_RAM     0xa5
#define SSD1780_COMM_DISP_NORM      0xa6
#define SSD1780_COMM_DISP_INVERSE   0xa7
#define SSD1780_COMM_MULTIPLEX      0xa8
#define SSD1780_COMM_VERT_OFFSET    0xd3
#define SSD1780_COMM_CLK_SET        0xd5
#define SSD1780_COMM_PRECHARGE      0xd9
#define SSD1780_COMM_COM_PIN        0xda
#define SSD1780_COMM_DESELECT_LV    0xdb
#define SSD1780_COMM_CONTRAST       0x81
#define SSD1780_COMM_DISABLE_SCROLL 0x2e
#define SSD1780_COMM_ENABLE_SCROLL  0x2f
#define SSD1780_COMM_PAGE_NUMBER    0xb0
#define SSD1780_COMM_LOW_COLUMN     0x00
#define SSD1780_COMM_HIGH_COLUMN    0x10

#define SSD1780_COMM_START_LINE     0x40

#define SSD1780_COMM_CHARGE_PUMP    0x8d

#define SSD1780_COMM_SCAN_NORM      0xc0
#define SSD1780_COMM_SCAN_REVS      0xc8

#define SSD1780_COMM_MEMORY_MODE    0x20
#define SSD1780_COMM_SET_COL_ADDR   0x21
#define SSD1780_COMM_SET_PAGE_ADDR  0x22

#define SSD1780_HORI_MODE           0x00
#define SSD1780_VERT_MODE           0x01
#define SSD1780_PAGE_MODE           0x02

#define SSD1780_FONT_SMALL          0x00
#define SSD1780_FONT_NORMAL         0x01

#define SSD1780_128_64_LINES        64
#define SSD1780_128_32_LINES        32
#define SSD1780_64_48_LINES         48

#define SSD1780_128_64_COLUMNS      128
#define SSD1780_128_32_COLUMNS      128
#define SSD1780_64_48_COLUMNS       64

extern uint8_t frame_buffer[1024];
// extern uint8_t data_buf[1026];

uint8_t SSD1780_init(uint8_t i2c_dev);
uint8_t SSD1780_defaultConfig();
uint8_t SSD1780_close();
uint8_t SSD1780_clear();
uint8_t SSD1780_invertDisplay();
void SSD1780_print2Buffer(uint8_t line, char* message);
void SSD1780_print2BufferLarge(uint8_t line, char* message);
void SSD1780_putPixel2Buffer(uint8_t x, uint8_t y);

void SSD1780_displayBuffer();

#endif