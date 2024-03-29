#ifndef _AES_H_
#define _AES_H_

#include <stdio.h>
#include <sanuwave_crf.h>

// USE this to test the AES algorithm against the NIST test vectors
//#define TEST_AES_MATH

// This is set in the APT.pro and CryptoLibTest.pro files
#ifdef AESLinked_STDINT
	// Some Data Types Used in AES.h and AES.c
	#include <stdint.h>
#else
#endif

// state - array holding the intermediate results during decryption.
typedef uint8_t state_t[4][4];

// Function Prototypes
void encryptBufferData(uint8_t *pHdrData, int len);
void decryptBufferData(uint8_t *pHdrData, int len);
#ifdef TEST_AES_MATH
    void testAESFunction(void);
#endif

#define AES_BLOCKLEN 16 //Block length in bytes AES is 128b block only
#define AES_KEYLEN 16   // Key length in bytes
#define AES_keyExpSize 176


struct AES_ctx
{
  uint8_t RoundKey[AES_keyExpSize];
  uint8_t Iv[AES_BLOCKLEN];
};

void AES_init_ctx(struct AES_ctx* ctx, const uint8_t* key);
void AES_init_ctx_iv(struct AES_ctx* ctx, const uint8_t* key, const uint8_t* iv);
void AES_ctx_set_iv(struct AES_ctx* ctx, const uint8_t* iv);



// buffer size MUST be mutile of AES_BLOCKLEN;
// Suggest https://en.wikipedia.org/wiki/Padding_(cryptography)#PKCS7 for padding scheme
// NOTES: you need to set IV in ctx via AES_init_ctx_iv() or AES_ctx_set_iv()
//        no IV should ever be reused with the same key 
void AES_CBC_encrypt_buffer(struct AES_ctx* ctx, uint8_t* buf, uint32_t length);
void AES_CBC_decrypt_buffer(struct AES_ctx* ctx, uint8_t* buf, uint32_t length);

#endif //_AES_H_
