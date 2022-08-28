/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "util.h"

extern void AES_128_keyschedule(unsigned char *rk);
extern void AES_128_encrypt(const unsigned char *, const unsigned char *, unsigned char *);


int main(void)
{
    unsigned char in[16] = {0x00, };
    unsigned char out[16];

    unsigned char rk[6*16] = {0x00, 0x00, 0x00, 0x00,
    							0x10, 0x00, 0x00, 0x00,
    							0x20, 0x00, 0x00, 0x00,
    							0x30, 0x00, };

    unsigned int* rk32 = (unsigned int*)rk;

    AES_128_keyschedule(rk);


    uint64_t oldcount = getcycles();
    for(int i=0; i<10000; i++) AES_128_encrypt(rk, in, out);
    uint64_t cyclecount = getcycles()-oldcount;

    printf("cyc: %d\n", (unsigned int)cyclecount);
//    AES_128_encrypt(rk, in, out);
//    // Print ciphertext
//    printf("out: ");
//    for (int i = 0; i < 16; ++i) {
//        printf("%02x ", out[i]);
//    }
//    printf("\n");

    return 0;
}

