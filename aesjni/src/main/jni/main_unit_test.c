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
#include <crypto_aead_aes256gcm.h>

/*
There is a testing for AEAD AES256_GCM.

generated AES key_hex          :d56aca0c41806fded2bad76c680a6664156f8d868b2fc7c51fba0f858ec910f4
generated AES nonce_hex        :2a42a84c3a82a1dcf1d83b07
*/
void test_aead_aes256gcm()
{

    /*
    AES256-GCM is not high performance on ARM.
    */

    // to detect CPU has hardware-accelerated for AES256GCM.
    if (crypto_aead_aes256gcm_is_available() == 0)
    {
        printf("This device doesn't support AES algorithm.\n=");
        LOGI("This device doesn't support AES algorithm."); /* Not available on this CPU */
    }
    else
    {
        LOGI("This device supports AES algorithm.");

        init_aes256();

        const char *key_hex = "d56aca0c41806fded2bad76c680a6664156f8d868b2fc7c51fba0f858ec910f4";
        const char *nonce_hex = "2a42a84c3a82a1dcf1d83b07";
        const unsigned char *key = aes_keyhex2bin(key_hex);
        const unsigned char *nonce = aes_noncehex2bin(nonce_hex);
        const size_t message_len = 4;
        const unsigned char *message = "test";

         if(crypto_aead_aes256gcm_beforenm(aes256gcm_ctx,key)==0){
             printf("aes beforenm called.");
         }

        unsigned char *ciphertext;
        unsigned long long found_ciphertext_len;
        crypto_aead_aes256gcm_encrypt_afternm(ciphertext, &found_ciphertext_len,
                                      message, message_len,
                                      "test", 4,
                                      NULL, nonce, aes256gcm_ctx);

        const unsigned char *decrypted;
        unsigned long long found_dec_len;
        crypto_aead_aes256gcm_decrypt_afternm(decrypted, &found_dec_len, NULL,
                                      ciphertext, found_ciphertext_len,
                                      "test", 4,
                                      nonce, aes256gcm_ctx);

        print_str(decrypted, (size_t)found_dec_len);
    }
}

//------------------------------------------------------------------------------------------

/*
    ChaCha20-Poly1305 is performance on ARM.
    */
void test_chacha20()
{
    is_debug();
    const char *PLAIN_TEXT = "test123中文END000";
    const unsigned int PLAIN_LEN = 15;
    const unsigned char *ADDITIONAL_DATA = NULL; //addtional data is used to verify data.
    const unsigned int ADDITIONAL_DATA_LEN = 0;

    //static key and nonce with hex.
    const char *key_hex = "9876c42f2f61bee24cc27ebd6155897c46950a83c9b0cc95a9650f9ae7421d07";
    const char *nonce_hex = "611dec2f53524315";
    const unsigned char *NONCE = chacha20_hexnonce2bin(nonce_hex);
    const unsigned char *KEY = chacha20_hexkey2bin(key_hex);

    LOGI("plain text:%s", PLAIN_TEXT);

    printf("PLAIN_TEXT\t:");
    print_str(PLAIN_TEXT, (size_t)PLAIN_LEN);

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
    print_str(decrypted, (size_t)decrypted_len);
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
    generate_aes_and_print();
    printf("\n");

    LOGI("-----------------------aead_aes256gcm----------------------");
    //test_aead_aes256gcm();

    LOGI("-----------------------chacha20----------------------");
    test_chacha20();

    LOGI("main()...end");

    return 0;
}
