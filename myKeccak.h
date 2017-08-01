/*
Author: Arpan Gupta
*/
/*
#ifndef KECCAK_1600
#define KECCAK_1600
#endif

#ifdef KECCAK_1600
#define LANE_WIDTH 64
#elif KECCAK_800
#define LANE_WIDTH 32
#elif KECCAK_400
#define LANE_WIDTH 16
#elif KECCAK_200
#define LANE_WIDTH 8
#elif KECCAK_100
#define LANE_WIDTH 4
#elif KECCAK_50
#define LANE_WIDTH 2
#elif KECCAK_25
#define LANE_WIDTH 1
#endif

#define STATE_ROW 5
#define STATE_COL 5

#ifdef KECCAK_1600
#define KEC_ROUNDS 24
#elif KECCAK_800
#define KEC_ROUNDS 22
#elif KECCAK_400
#define KEC_ROUNDS 20
#elif KECCAK_200
#define KEC_ROUNDS 18
#elif KECCAK_100
#define KEC_ROUNDS 16
#elif KECCAK_50
#define KEC_ROUNDS 14
#elif KECCAK_25
#define KEC_ROUNDS 12
#endif

#define ROTL64(x, y) (((x)<<(y))|((x)>>(64-(y))))
#include<stdint.h>

unsigned long permute();

void keccak_f(const uint32_t *in, unsigned long inlen, const uint32_t *out, unsigned long hashLen);

uint32_t* keccak_pad(const uint32_t *in, unsigned long inlen);
*/