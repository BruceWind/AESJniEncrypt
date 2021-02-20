/*===================================================
this file is used to test native codes.
you can run a command in this directory: ./rebuild.sh test
===================================================*/

#define TEST_NAME "aead_aes256gcm"
#include <stdio.h>
#include <logger.h>
#include <sodium.h>
#include <base64.h>
#include <stdlib.h>
#include <keys_generator.h>
#include <assert.h>

/*
There is a testing for AEAD AES256_GCM.
*/
void test_aead_aes256gcm()
{
    unsigned char *ad;
    unsigned char *ciphertext;
    unsigned char *decrypted;
    unsigned char *detached_ciphertext;
    unsigned char *expected_ciphertext;
    unsigned char *key;
    unsigned char *mac;
    unsigned char *nonce;
    char *hex;
    unsigned long long found_ciphertext_len;
    unsigned long long found_mac_len;
    unsigned long long found_message_len;
    size_t ad_len;
    size_t ciphertext_len;
    size_t detached_ciphertext_len;
    size_t i = 0U;

    /*
    AES256-GCM is not high performance on ARM.
    */

    // to detect CPU has hardware-accelerated for AES256GCM.
    if (crypto_aead_aes256gcm_is_available() == 0)
    {
        LOGD("The device doesn't support AES algorithm."); /* Not available on this CPU */
    }
    else
    {
        LOGD("The device support AES algorithm.");

        const char *key_hex = "b52c505a37d78eda5dd34f20c22540ea1b58963cf8e5bf8ffa85f9f2492505b4";
        const char *nonce_hex = "516c33929df5a3284ff463d7";
        const char *mac_hex = "bdc1ac884d332457a1d2664f168c76f0";

        const size_t message_len = 4;
        const unsigned char *message = "test";

        key = (unsigned char *)sodium_malloc(crypto_aead_aes256gcm_KEYBYTES);
        nonce = (unsigned char *)sodium_malloc(crypto_aead_aes256gcm_NPUBBYTES);
        mac = (unsigned char *)sodium_malloc(crypto_aead_aes256gcm_ABYTES);

        sodium_hex2bin(key, crypto_aead_aes256gcm_KEYBYTES,
                       key_hex, strlen(key_hex),
                       NULL, NULL, NULL);
        sodium_hex2bin(nonce, crypto_aead_aes256gcm_NPUBBYTES,
                       nonce_hex, strlen(nonce_hex),
                       NULL, NULL, NULL);

        crypto_aead_aes256gcm_encrypt(ciphertext, &found_ciphertext_len,
                                      message, message_len,
                                      NULL, 0, NULL, nonce, key);

        crypto_aead_aes256gcm_decrypt(NULL, NULL, NULL, ciphertext, strlen(ciphertext),
                                      NULL, 0, nonce, key);
    }
}

//------------------------------------------------------------------------------------------

/*
    ChaCha20-Poly1305 is performance on ARM.
    */
void test_chacha20()
{
    const char *PLAIN_TEXT = "test123中文END000";
    const unsigned int PLAIN_LEN = 15;
    const unsigned char *ADDITIONAL_DATA = NULL;//addtional data is used to verify data.
    const unsigned int ADDITIONAL_DATA_LEN = 0;

    //static key and nonce with hex.
    const char *key_hex="9876c42f2f61bee24cc27ebd6155897c46950a83c9b0cc95a9650f9ae7421d07";
    const char *nonce_hex="611dec2f53524315";
    const unsigned char *NONCE = chacha20_hexnonce2bin(nonce_hex);
    const unsigned char *KEY = chacha20_hexkey2bin(key_hex);
    
    LOGI("plain text:%s", PLAIN_TEXT);

    printf("PLAIN_TEXT\t:");
    print_str(PLAIN_TEXT,(size_t)PLAIN_LEN);

    printf("PLAIN_TEXT hex\t:");
    print_chars_in_hex(PLAIN_TEXT, (size_t)PLAIN_LEN);

    unsigned char *ciphertext;
    ciphertext = (unsigned char *)sodium_malloc(PLAIN_LEN + crypto_aead_chacha20poly1305_ABYTES);
    unsigned long long ciphertext_len;

    crypto_aead_chacha20poly1305_encrypt(ciphertext, &ciphertext_len,
                                         PLAIN_TEXT, PLAIN_LEN,
                                         ADDITIONAL_DATA, ADDITIONAL_DATA_LEN, //additional data is NULL.
                                         NULL, NONCE, KEY);

    unsigned char *decrypted;
    decrypted = (unsigned char *)sodium_malloc(PLAIN_LEN);
    unsigned long long decrypted_len;
    crypto_aead_chacha20poly1305_decrypt(decrypted, &decrypted_len,
                                         NULL,
                                         ciphertext, ciphertext_len,
                                         ADDITIONAL_DATA, ADDITIONAL_DATA_LEN,
                                         NONCE, KEY);
    if (decrypted_len != PLAIN_LEN)
    {
        printf("wrong\t:");
        abort(); //you won't see "main() end" in terminal.
    }

    printf("decrypted\t:");
    print_str(decrypted,(size_t)decrypted_len);
    printf("decrypted hex\t:");
    print_chars_in_hex(decrypted, (size_t)decrypted_len);

    sodium_free(ciphertext);
    sodium_free(decrypted);
}

int main()
{

    LOGI("main()...begin");

    sodium_init();

    LOGI("-----------------------generate_and_print----------------------");
    generate_chacah20_and_print();

    LOGI("-----------------------aead_aes256gcm----------------------");
    //test_aead_aes256gcm();

    LOGI("-----------------------chacha20----------------------");
    test_chacha20();

    LOGI("main()...end");

    return 0;
}
