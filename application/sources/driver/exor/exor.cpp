#include "exor.h"

void exor_encrypt_decrypt(uint8_t* input, uint8_t* output, uint32_t size, uint8_t* key, uint32_t key_size) {
	for (uint32_t i = 0; i < size; i++) {
		output[i] = input[i] ^ key[i % key_size];
	}
}
