/* sodium.i */
%module Sodium
%include "typemaps.i"

/**
 * Defines unsigned char * (C) -> byte[] (Java)
 *
 * Following is taken from SWIG's various.i and adapted for unsigned chars 
 */
%typemap(jni) unsigned char *BYTE "jbyteArray"
%typemap(jtype) unsigned char *BYTE "byte[]"
%typemap(jstype) unsigned char *BYTE "byte[]"
%typemap(in) unsigned char *BYTE {
  $1 = (unsigned char *) JCALL2(GetByteArrayElements, jenv, $input, 0); 
}

%typemap(argout) unsigned char *BYTE {
  JCALL3(ReleaseByteArrayElements, jenv, $input, (jbyte *) $1, 0); 
}

%typemap(javain) unsigned char *BYTE "$javainput"

/* Prevent default freearg typemap from being used */
%typemap(freearg) unsigned char *BYTE ""

%apply unsigned char *BYTE { unsigned char * }; 

/* See Above.
 * Previous is taken from SWIG's various.i and adapted for unsigned chars 
 **/


/* SWIG uses BigInts for unsigned long longs, but BigInts are obnoxious
 * and so we'd like to use a java long. typemaps.i defines unsigned long as a java long,
 * so although we do lose 'unsigned', hopefully we can rely on the callers not to pass in
 * a negative size.
 */
%apply unsigned long { unsigned long long };

/* Since this is only used by the randombytes (so far), then we're limited by an int (buf.length) */
%apply int { size_t };

%apply int { uint32_t };
%apply unsigned char *BYTE { void * const };

/* Following needed to make sure we don't use String type for hashes */
%apply unsigned char *BYTE { const char str[crypto_pwhash_scryptsalsa208sha256_STRBYTES] };
%apply unsigned char *BYTE { char out[crypto_pwhash_scryptsalsa208sha256_STRBYTES] };

%javaconst(1);

/* Start Sodium Definitions */
%{
#include "sodium.h"
%}

/* core.h */
int sodium_init(void);

const char *sodium_version_string(void);


/* randombytes.h */

void randombytes_buf(void * const buf, const size_t size);

uint32_t randombytes_random(void);

uint32_t randombytes_uniform(const uint32_t upper_bound);

/* crypto_sign.h & crypto_sign_*.h */

#define CRYPTO_SIGN_BYTES 64 
#define CRYPTO_SIGN_SEEDBYTES 32 
#define CRYPTO_SIGN_PUBLICKEYBYTES 32
#define CRYPTO_SIGN_SECRETKEYBYTES (32 + 32)

int crypto_sign_keypair(unsigned char *pk, unsigned char *sk);

int crypto_sign_seed_keypair(unsigned char *pk, unsigned char *sk,
                             const unsigned char *seed);

int crypto_sign(unsigned char *sm, unsigned long long *smlem,
                const unsigned char *m, unsigned long long mlen,
                const unsigned char *sk);

int crypto_sign_open(unsigned char *m, unsigned long long *mlen,
                     const unsigned char *sm, unsigned long long smlen,
                     const unsigned char *pk);

int crypto_sign_detached(unsigned char *sig, unsigned long long *slen,
                         const unsigned char *m, unsigned long long mlen,
                         const unsigned char *sk);


int crypto_sign_ed25519_sk_to_curve25519(unsigned char *curve25519_sk,
                                         const unsigned char *ed25519_sk);

int crypto_sign_ed25519_pk_to_curve25519(unsigned char *curve25519_pk,
                                         const unsigned char *ed25519_pk);

int crypto_sign_verify_detached(const unsigned char *sig,
                                const unsigned char *m,
                                unsigned long long mlen,
                                const unsigned char *pk);

int crypto_sign_ed25519_sk_to_seed(unsigned char *seed,
                                   const unsigned char *sk);

int crypto_sign_ed25519_sk_to_pk(unsigned char *pk, const unsigned char *sk);

/* crypto_box.h */

#define CRYPTO_BOX_SEEDBYTES 32
#define CRYPTO_BOX_PUBLICKEYBYTES 32
#define CRYPTO_BOX_SECRETKEYBYTES 32 
#define CRYPTO_BOX_NONCEBYTES 24
#define CRYPTO_BOX_MACBYTES 16

int crypto_box_seed_keypair(unsigned char *pk, unsigned char *sk,
                            const unsigned char *seed);

int crypto_box_keypair(unsigned char *pk, unsigned char *sk);

int crypto_box_easy(unsigned char *c, const unsigned char *m,
                    unsigned long long mlen, const unsigned char *n,
                    const unsigned char *pk, const unsigned char *sk);


int crypto_box_open_easy(unsigned char *m, const unsigned char *c,
                         unsigned long long clen, const unsigned char *n,
                         const unsigned char *pk, const unsigned char *sk);

int crypto_box_detached(unsigned char *c, unsigned char *mac,
                        const unsigned char *m, unsigned long long mlen,
                        const unsigned char *n, const unsigned char *pk,
                        const unsigned char *sk);

int crypto_box_open_detached(unsigned char *m, const unsigned char *c,
                             const unsigned char *mac,
                             unsigned long long clen,
                             const unsigned char *n,
                             const unsigned char *pk,
                             const unsigned char *sk);


/* crypto_secret_box.h & crypto_secret_box_*.h */

#define CRYPTO_SECRETBOX_KEYBYTES 32
#define CRYPTO_SECRETBOX_MACBYTES 16 
#define CRYPTO_SECRETBOX_NONCEBYTES 24

int crypto_secretbox_easy(unsigned char *c, const unsigned char *m,
                          unsigned long long mlen, const unsigned char *n,
                          const unsigned char *k);

int crypto_secretbox_open_easy(unsigned char *m, const unsigned char *c,
                               unsigned long long clen, const unsigned char *n,
                               const unsigned char *k);

int crypto_secretbox_detached(unsigned char *c, unsigned char *mac,
                              const unsigned char *m,
                              unsigned long long mlen,
                              const unsigned char *n,
                              const unsigned char *k);

int crypto_secretbox_open_detached(unsigned char *m,
                                   const unsigned char *c,
                                   const unsigned char *mac,
                                   unsigned long long clen,
                                   const unsigned char *n,
                                   const unsigned char *k);

/* crypto_auth.h */

#define CRYPTO_AUTH_BYTES 32
#define CRYPTO_AUTH_KEYBYTES 32

int crypto_auth(unsigned char *out, const unsigned char *in,
                unsigned long long inlen, const unsigned char *k);


int crypto_auth_verify(const unsigned char *h, const unsigned char *in,
                       unsigned long long inlen, const unsigned char *k);

/* crypto_aead.h */

#define CRYPTO_AED_CHACHA20POLY1305_KEYBYTES 32
#define CRYPTO_AED_CHACHA20POLY1305_NONCEBYTES 32
#define CRYPTO_AED_CHACHA20POLY1305_MACBYTES 16 

int crypto_aead_chacha20poly1305_encrypt(unsigned char *c,
                                         unsigned long long *clen,
                                         const unsigned char *m,
                                         unsigned long long mlen,
                                         const unsigned char *ad,
                                         unsigned long long adlen,
                                         const unsigned char *nsec,
                                         const unsigned char *npub,
                                         const unsigned char *k);

int crypto_aead_chacha20poly1305_decrypt(unsigned char *m,
                                         unsigned long long *mlen,
                                         unsigned char *nsec,
                                         const unsigned char *c,
                                         unsigned long long clen,
                                         const unsigned char *ad,
                                         unsigned long long adlen,
                                         const unsigned char *npub,
                                         const unsigned char *k);

/* crypto_pwhash_*.h */

#define CRYPTO_PWHASH_SALTBYTES 32
#define CRYPTO_PWHASH_HASHBYTES 102 
#define CRYPTO_PWHASH_KEY_BYTES 32

#define CRYPTO_PWHASH_OPSLIMIT_INTERACTIVE 524288
#define CRYPTO_PWHASH_MEMLIMIT_INTERACTIVE 16777216

#define CRYPTO_PWHASH_OPSLIMIT_SENSITIVE 33554432
#define CRYPTO_PWHASH_MEMLIMIT_SENSITIVE 1073741824

int crypto_pwhash_scryptsalsa208sha256(unsigned char * const out,
                                       unsigned long long outlen,
                                       const char * const passwd,
                                       unsigned long long passwdlen,
                                       const unsigned char * const salt,
                                       unsigned long long opslimit,
                                       size_t memlimit);

int crypto_pwhash_scryptsalsa208sha256_str(char out[crypto_pwhash_scryptsalsa208sha256_STRBYTES],
                                           const char * const passwd,
                                           unsigned long long passwdlen,
                                           unsigned long long opslimit,
                                           size_t memlimit);

int crypto_pwhash_scryptsalsa208sha256_str_verify(const char str[crypto_pwhash_scryptsalsa208sha256_STRBYTES],
                                                  const char * const passwd,
                                                  unsigned long long passwdlen);

/* crypto_shorthash.h */

#define CRYPTO_SHORTHASH_BYTES 8 
#define CRYPTO_SHORTHASH_KEYBYTES 16 

int crypto_shorthash(unsigned char *out, const unsigned char *in,
                     unsigned long long inlen, const unsigned char *k);


/* crypto_generichash.h */

#define CRYPTO_GENERICHASH_BYTES 32
#define CRYPTO_GENERICHASH_KEYBYTES 32

int crypto_generichash(unsigned char *out, size_t outlen,
                       const unsigned char *in, unsigned long long inlen,
                       const unsigned char *key, size_t keylen);


/* TODO: Need to figure out how to represent crypto_generichash_state with SWIG

int crypto_generichash_init(crypto_generichash_state *state,
                            const unsigned char *key,
                            const size_t keylen, const size_t outlen);

int crypto_generichash_update(crypto_generichash_state *state,
                              const unsigned char *in,
                              unsigned long long inlen);

int crypto_generichash_final(crypto_generichash_state *state,
                             unsigned char *out, const size_t outlen);

*/


/* */

/* Static library loader */

%pragma(java) jniclasscode = %{
        /* Load JNI library */
        static {
                try {
                    System.loadLibrary("JNIEncrypt");
                    if (sodium_init() == -1) {
                        throw new RuntimeException("Sodium could not be initialized.");
                    }
                } catch (Exception e) {
                        e.printStackTrace();
                        System.exit(1);
                }
        }
%} 
