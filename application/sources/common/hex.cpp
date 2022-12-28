#include "hex.h"

void bytetoHexChar(uint8_t ubyte, uint8_t *uHexChar) {
    uHexChar[1] = ((ubyte & 0x0F) < 10) ? ((ubyte & 0x0F) + '0') : (((ubyte & 0x0F) - 10) + 'A');
    uHexChar[0] = ((ubyte >> 4 & 0x0F) < 10) ? ((ubyte >> 4 & 0x0F) + '0') : (((ubyte >> 4 & 0x0F) - 10) + 'A');
}

void bytestoHexChars(uint8_t *ubyte, int32_t len, uint8_t *uHexChar) {
    for (int8_t i = 0; i < len; i++) {
        bytetoHexChar(ubyte[i], (uint8_t*) &uHexChar[i * 2]);
    }
}

void hexChartoByte(uint8_t *uHexChar, uint8_t *ubyte) {

    *ubyte = 0;
    *ubyte = ((uHexChar[0] <= '9' && uHexChar[0] >= '0') ? ((uHexChar[0] - '0') << 4) : *ubyte);
    *ubyte = ((uHexChar[0] <= 'F' && uHexChar[0] >= 'A') ? ((uHexChar[0] - 'A' + 10) << 4) : *ubyte);

    *ubyte = ((uHexChar[1] <= '9' && uHexChar[1] >= '0') ? *ubyte | (uHexChar[1] - '0') : *ubyte);
    *ubyte = ((uHexChar[1] <= 'F' && uHexChar[1] >= 'A') ? *ubyte | ((uHexChar[1] - 'A') + 10) : *ubyte);

}

void hexCharsToBytes(uint8_t *uHexChar, int32_t len, uint8_t *ubyte) {
    for (int8_t i = 0; i < len; i += 2) {
        hexChartoByte((uint8_t*) &uHexChar[i], (uint8_t *) &ubyte[i / 2]);
    }
}
