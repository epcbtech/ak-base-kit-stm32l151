#ifndef __EXOR_H__
#define __EXOR_H__

#include <stdint.h>

extern void exor_encrypt_decrypt(uint8_t* input, uint8_t* output, uint32_t size, uint8_t* key, uint32_t key_size);

#endif //__EXOR_H__
