#ifndef _ENCODER_H_
#define _ENCODER_H_

// Returns direction of the encoder
// -1: left, 0: NULL, 1: right, 3: left+click, -3: right+click
int getEncoderInput(short chClick, short chLeft, short chRight);

#endif