/*===================================================
this file is used to test native codes.
you can run a command in this directory: ./rebuild.sh test
===================================================*/

#define TEST_NAME "aead_aes256gcm"
#include <stdio.h>
#include <android/log.h>
#include <sodium.h>
#include <base64.h>
#include <stdlib.h>
// #include <assert.h>


#define TAG "NATIVE_UT"
void logd(char *str)
{
    //this string will be got from you command.
    printf("%s \n", str);
    //run "adb logcat | grep NATIVE_UT" in order to seek logs.
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "%s", str);
}

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
        logd("The device doesn't support AES algorithm."); /* Not available on this CPU */
    }
    else
    {
        logd("The device support AES algorithm.");

        const char *key_hex             = "b52c505a37d78eda5dd34f20c22540ea1b58963cf8e5bf8ffa85f9f2492505b4";
        const char *nonce_hex           = "516c33929df5a3284ff463d7";
        const char *mac_hex             = "bdc1ac884d332457a1d2664f168c76f0";

        const size_t message_len        = 4;
        const unsigned char *message    = "test";

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

/*
    ChaCha20-Poly1305 is performance on ARM.
    */
void test_chacha20()
{
    const unsigned char     *PLAIN_TEXT             = "test1234test1234test1234test1234END";
    const unsigned int      PLAIN_LEN               = 35;
    const unsigned char     *ADDITIONAL_DATA        = NULL;
    const unsigned int      ADDITIONAL_DATA_LEN     = 0;

    //static key and nonce with base64encode.

    // unsigned char nonce[crypto_aead_chacha20poly1305_NPUBBYTES];
    // unsigned char key[crypto_aead_chacha20poly1305_KEYBYTES];
    // crypto_aead_chacha20poly1305_keygen(key);
    // randombytes_buf(nonce, sizeof nonce);

    //key & nonce were generated with random.
    const unsigned char     *BASE64_NONCE   = "wzAeemDo5oY=";
    const unsigned char     *BASE64_KEY     = "cU3wmpJ0cmfMHSWVKbmH4GkU4CBnfARePp1GdrSwQObDMB56YOjmhg==";
    char                    *nonce          = b64_decode(BASE64_NONCE, strlen(BASE64_NONCE));
    char                    *key            = b64_decode(BASE64_KEY, strlen(BASE64_KEY));

    logd("key:");       logd(b64_encode(key, strlen(key)));

    char a =key[strlen(key)-1];
    int ia = (int)a;
    printf("last of key: %d\n",ia);

    logd("nonce:");     logd(b64_encode(nonce, strlen(nonce)));

    unsigned char ciphertext[PLAIN_LEN  + crypto_aead_chacha20poly1305_ABYTES];
    unsigned long long ciphertext_len;


    crypto_aead_chacha20poly1305_encrypt(ciphertext, &ciphertext_len,
                                         PLAIN_TEXT, PLAIN_LEN,
                                         ADDITIONAL_DATA, ADDITIONAL_DATA_LEN, //additional data is NULL.
                                         NULL, nonce, key);

    logd("encrypted text:  ");          logd(b64_encode(ciphertext, ciphertext_len));

    char decrypted[PLAIN_LEN];
    unsigned long long decrypted_len;
    crypto_aead_chacha20poly1305_decrypt(decrypted, &decrypted_len,
                                             NULL,
                                             ciphertext, ciphertext_len,
                                             ADDITIONAL_DATA,ADDITIONAL_DATA_LEN,
                                             nonce, key);
    logd("decrypted text:");
    logd(decrypted);

    if(strcmp(decrypted,PLAIN_TEXT)!=0){
        abort(); //you won't see "main() end" in terminal.
    }
    free(ciphertext);
    free(decrypted);
    free(PLAIN_TEXT);


}

int main()
{

    logd("main()...begin");

    sodium_init();

    logd("-----------------------aead_aes256gcm----------------------");
    test_aead_aes256gcm();

    logd("-----------------------chacha20----------------------");
    test_chacha20();

    logd("main()...end");

    return 0;
}
