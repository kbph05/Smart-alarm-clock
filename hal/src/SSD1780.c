#define _GNU_SOURCE

#include "hal/SSD1780.h"

#define SSD1780_COLUMNADDR 0x21
#define SSD1780_PAGEADDR 0x22
#define SSD1780_BUFFERSIZE 8


uint8_t ssd1306_init(uint8_t i2c_dev)
{
    uint8_t rc;
    rc = _i2c_init(i2c_dev, SSD1780_I2C_ADDR);
    if (rc > 0)
        return rc;
        
    // test i2c connection
    uint8_t cmd = SSD1780_COMM_CONTROL_BYTE;
    uint8_t result = 0;
    _i2c_write(&cmd, 1);
    _i2c_read(&result, 1);
    if (result == 0)
        return 1;
    
    return 0;
}

uint8_t ssd1306_end()
{
    return _i2c_close();
}
