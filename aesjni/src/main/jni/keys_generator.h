#include <stdio.h>
#include <sodium.h>
//    ----generate key and nonce----

static const unsigned int chacha20_key_len = crypto_aead_chacha20poly1305_KEYBYTES;
static const unsigned int chacha20_nonce_len = crypto_aead_chacha20poly1305_NPUBBYTES;
static const unsigned int chacha20_key_hex_len = chacha20_key_len * 2 + 1;
static const unsigned int chacha20_nonce_hex_len = chacha20_nonce_len * 2 + 1;
void generate_chacah20_and_print();
unsigned char* chacha20_hexkey2bin(char * hex);
unsigned char* chacha20_hexnonce2bin(char * hex);


void generate_aes_and_print();
unsigned char* aes_hexkey2bin(char * hex);
unsigned char* aes_hexnonce2bin(char * hex);
