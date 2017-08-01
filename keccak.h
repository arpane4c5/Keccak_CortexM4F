/* keccak.h
Author: Arpan Gupta
Description: This file contains the declarations and globals required for Keccak
*/

#ifndef KECCAK_H
#define KECCAK_H

#include<stdint.h>
#include<string.h>
#include<stdlib.h>

#ifndef KECCAK_ROUNDS
#define KECCAK_ROUNDS 24
#endif

#ifndef ROTL64
#define ROTL64(x, y) (((x)<<(y))|((x)>>(64-(y))))
#endif

//compute a keccak hash (md) of given byte length from "in"
void keccak(uint8_t *in, unsigned long inlen, uint8_t *md, unsigned long mdlen);

//update the state
void keccakf(uint64_t st[25], unsigned long rounds);

#endif
