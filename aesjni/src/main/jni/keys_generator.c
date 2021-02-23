#include "keys_generator.h"

void generate_chacah20_and_print()
{
    unsigned char key[chacha20_key_len];
    unsigned char nonce[chacha20_nonce_len];
    randombytes_buf(nonce, sizeof nonce);
    crypto_aead_chacha20poly1305_keygen(key);

    char *key_hex = (char *)sodium_malloc(chacha20_key_hex_len);
    sodium_bin2hex(key_hex, (size_t)(chacha20_key_hex_len), key, chacha20_key_len);
    printf("generate a chacha20 key_hex \t:%s\n", key_hex);
    //test key hex2bin
    chacha20_hexnonce2bin(key_hex);

    char *nonce_hex = (char *)sodium_malloc(chacha20_nonce_hex_len);
    sodium_bin2hex(nonce_hex, (size_t)(chacha20_nonce_hex_len), nonce, chacha20_nonce_len);
    printf("generate a chacha20 nonce_hex\t:%s\n", nonce_hex);

    //test nonce hex2bin
    chacha20_hexnonce2bin(nonce_hex);
    sodium_free(nonce_hex);
    sodium_free(key_hex);
}

/**strlen(hex) must equal to chacha20_key_hex_len 
 * dont forget to free char *.
*/
unsigned char *chacha20_hexkey2bin(char *hex)
{
    unsigned char *out_key = (unsigned char *)sodium_malloc(chacha20_key_len);
    sodium_hex2bin(out_key, chacha20_key_len,
                   hex, chacha20_key_hex_len,
                   NULL, NULL, NULL);
    return out_key;
}

//strlen(hex) must equal to chacha20_nonce_hex_len
unsigned char *chacha20_hexnonce2bin(char *hex)
{
    unsigned char *out_nonce = (unsigned char *)sodium_malloc(chacha20_nonce_len);
    sodium_hex2bin(out_nonce, chacha20_nonce_len,
                   hex, chacha20_nonce_hex_len,
                   NULL, NULL, NULL);
    return out_nonce;
}


//call this must
void init_aes256(){
    aes256gcm_ctx = sodium_malloc(sizeof(AES256GCM_CTX));
    memset(aes256gcm_ctx, 0, sizeof(AES256GCM_CTX));
}


void generate_aes_and_print()
{
    unsigned char nonce[aes_nonce_len];
    unsigned char key[aes_key_len];
    
    crypto_aead_aes256gcm_keygen(key);
    randombytes_buf(nonce, sizeof nonce);
    char *key_hex = (char *)sodium_malloc(aes_key_hex_len);
    sodium_bin2hex(key_hex, (size_t)(aes_key_hex_len), key, aes_key_len);
    printf("generate a AES key_hex\t\t:%s\n", key_hex);
    // test keyhex
    aes_keyhex2bin(key_hex);

    char *nonce_hex = (char *)sodium_malloc(aes_nonce_hex_len);
    sodium_bin2hex(nonce_hex, (size_t)(aes_nonce_hex_len), nonce, aes_nonce_len);
    printf("generate a AES nonce_hex\t:%s\n", nonce_hex);

    //test 
    aes_noncehex2bin(nonce_hex);
}

unsigned char *aes_keyhex2bin(char *hex)
{
    unsigned char *out_key = (unsigned char *)sodium_malloc(aes_key_len);
    sodium_hex2bin(out_key, aes_key_len,
                   hex, aes_key_hex_len,
                   NULL, NULL, NULL);
    return out_key;
}

unsigned char *aes_noncehex2bin(char *hex)
{
    unsigned char *out_nonce = (unsigned char *)sodium_malloc(aes_nonce_len);
    sodium_hex2bin(out_nonce, aes_nonce_len,
                   hex, aes_nonce_hex_len,
                   NULL, NULL, NULL);
    return out_nonce;
}
