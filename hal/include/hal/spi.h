#ifndef _SPI_H_
#define _SPI_H_

// reads spi device on specified channel at specified speed
int spiRead(int ch, unsigned long speed_hz);
// returns average readings for consistancy to avoid blips
int spiReadAverage(int ch, unsigned long speed_hz, int samples);

#endif