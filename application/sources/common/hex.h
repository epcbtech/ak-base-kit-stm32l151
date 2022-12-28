#ifndef HEX_H
#define HEX_H

#include <stdint.h>

extern void bytetoHexChar(uint8_t ubyte, uint8_t *uHexChar);
extern void bytestoHexChars(uint8_t *ubyte, int32_t len, uint8_t *uHexChar);
extern void hexChartoByte(uint8_t *uHexChar, uint8_t *ubyte);
extern void hexCharsToBytes(uint8_t *uHexChar, int32_t len, uint8_t *ubyte);

#endif // HEX_H
