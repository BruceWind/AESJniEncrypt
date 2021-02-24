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



//it is important to be used for AES256.
typedef crypto_aead_aes256gcm_state AES256GCM_CTX;

//only one aes256gcm context.
static AES256GCM_CTX *aes256gcm_ctx;
void init_aes256();

static const unsigned int aes_key_len = crypto_aead_aes256gcm_KEYBYTES;
static const unsigned int aes_nonce_len = crypto_aead_aes256gcm_NPUBBYTES;
static const unsigned int aes_key_hex_len = aes_key_len * 2 + 1;
static const unsigned int aes_nonce_hex_len = aes_nonce_len * 2 + 1;
void generate_aes_and_print();
unsigned char* aes_keyhex2bin(char * hex);
unsigned char* aes_noncehex2bin(char * hex);
