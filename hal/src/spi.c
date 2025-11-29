// Main program to build the application
// Has main(); does initialization and cleanup and perhaps some basic logic.

#define DA_TRIGGER_FILE "/sys/class/leds/ACT/trigger"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

int spiRead(int ch, unsigned long speed_hz) {
    //Initialize SPI interface
    const char* dev = "/dev/spidev0.0";
    uint8_t mode = 0; // SPI mode 0
    uint8_t bits = 8;
    uint32_t speed = 250000;

    int fd = open(dev, O_RDWR);

    if (fd < 0) { perror("open"); return 1; }
    if (ioctl(fd, SPI_IOC_WR_MODE, &mode) == -1) { 
        perror("mode"); 
        return 1; 
    }
    if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits) == -1) { 
        perror("bpw");
        return 1; 
    }
    if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed) == -1) { 
        perror("speed"); 
        return 1; 
    }
    //Read data
    uint8_t tx[3] = { (uint8_t)(0x06 | ((ch & 0x04) >> 2)),
                        (uint8_t)((ch & 0x03) << 6),
                        0x00 };
    uint8_t rx[3] = { 0 };

    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long)tx,
        .rx_buf = (unsigned long)rx,
        .len = 3,
        .speed_hz = speed_hz,
        .bits_per_word = 8,
        .cs_change = 0
    };

    if (ioctl(fd, SPI_IOC_MESSAGE(1), &tr) < 1) return -1;
    //Close and return
    close(fd);
    return ((rx[1] & 0x0F) << 8) | rx[2]; // 12-bit result
}
int spiReadAverage(int ch, unsigned long speed_hz, int samples) {
    int sample_sum = 0;
    for (int i = 0; i < samples; i++) {
        sample_sum = sample_sum + spiRead(ch, speed_hz);
    }
    return sample_sum/samples;
}