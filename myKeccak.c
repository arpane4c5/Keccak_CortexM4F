//#include "myKeccak.h"

///*
//#ifdef KECCAK_1600
//uint64_t state[25]=
//{
//	0,0,0,0,0,
//	0,0,0,0,0,
//	0,0,0,0,0,
//	0,0,0,0,0,
//	0,0,0,0,0
//};
//#elif KECCAK_800
//uint32_t state[25]=
//{
//	{0,0,0,0,0},
//	{0,0,0,0,0},
//	{0,0,0,0,0},
//	{0,0,0,0,0},
//	{0,0,0,0,0}
//};
//#elif KECCAK_400
//uint16_t state[25]=
//{
//	{0,0,0,0,0},
//	{0,0,0,0,0},
//	{0,0,0,0,0},
//	{0,0,0,0,0},
//	{0,0,0,0,0}
//};
//#else
//uint8_t state[25]=
//{
//	{0,0,0,0,0},
//	{0,0,0,0,0},
//	{0,0,0,0,0},
//	{0,0,0,0,0},
//	{0,0,0,0,0}
//};
//#endif
//*/

//const uint64_t iota_rnd_const[24] = 
//{
//    0x0000000000000001, 0x0000000000008082, 0x800000000000808a,
//    0x8000000080008000, 0x000000000000808b, 0x0000000080000001,
//    0x8000000080008081, 0x8000000000008009, 0x000000000000008a,
//    0x0000000000000088, 0x0000000080008009, 0x000000008000000a,
//    0x000000008000808b, 0x800000000000008b, 0x8000000000008089,
//    0x8000000000008003, 0x8000000000008002, 0x8000000000000080, 
//    0x000000000000800a, 0x800000008000000a, 0x8000000080008081,
//    0x8000000000008080, 0x0000000080000001, 0x8000000080008008
//};

//const int rho_rot_const[24] = 
//{
//    1,  3,  6,  10, 15, 21, 28, 36, 45, 55, 2,  14, 
//    27, 41, 56, 8,  25, 43, 62, 18, 39, 61, 20, 44
//};

//const int pi_lane_const[24] = 
//{
//    10, 7,  11, 17, 18, 3, 5,  16, 8,  21, 24, 4, 
//    15, 23, 19, 13, 12, 2, 20, 14, 22, 9,  6,  1 
//};

//unsigned long permute()
//{
//	return 0;
//}

////hashLen for 512 = 16, for 256 = 8
//void keccak_f(const uint32_t *in, unsigned long inlen, const uint32_t *out, unsigned long hashLen)
//{
//	int i, j, round;
//	uint64_t temp_plane[5], temp_lane;
//	uint64_t st2;
//	uint64_t state[25]=
//	{
//		0,1,2,3,0,
//		0,0,0,0,0,
//		0,0,0,0,0,
//		0,0,0,0,0,
//		0,0,0,0,0
//	};
//	uint32_t *st32=(uint32_t *)state;
//	uint64_t *st1=state;
//	round=0;

//	for(i=0;i<50;i++)
//		st32;
//	/*
//	    UINT32 * pI = (UINT32 *)out;
//    const UINT32 * pS = state;
//    UINT32 t, x0, x1;
//    int i;
//    for (i = laneCount-1; i >= 0; --i)
//    {
//        x0 = *(pS++);
//        x1 = *(pS++);
//        t = (x0 & 0x0000FFFF) | (x1 << 16);
//        x1 = (x0 >> 16) | (x1 & 0xFFFF0000);
//        x0 = t;
//        t = (x0 ^ (x0 >>  8)) & 0x0000FF00UL;  x0 = x0 ^ t ^ (t <<  8);
//        t = (x0 ^ (x0 >>  4)) & 0x00F000F0UL;  x0 = x0 ^ t ^ (t <<  4);
//        t = (x0 ^ (x0 >>  2)) & 0x0C0C0C0CUL;  x0 = x0 ^ t ^ (t <<  2);
//        t = (x0 ^ (x0 >>  1)) & 0x22222222UL;  x0 = x0 ^ t ^ (t <<  1);
//        t = (x1 ^ (x1 >>  8)) & 0x0000FF00UL;  x1 = x1 ^ t ^ (t <<  8);
//        t = (x1 ^ (x1 >>  4)) & 0x00F000F0UL;  x1 = x1 ^ t ^ (t <<  4);
//        t = (x1 ^ (x1 >>  2)) & 0x0C0C0C0CUL;  x1 = x1 ^ t ^ (t <<  2);
//        t = (x1 ^ (x1 >>  1)) & 0x22222222UL;  x1 = x1 ^ t ^ (t <<  1);
//        *(pI++) = x0;
//        *(pI++) = x1;
//    }
//		*/
//	
//	//theta
//	//Implementation 1: 989 states : 13% Code
//		for(i=0;i<5;i++)
//		{
//			temp_plane[i] = state[i] ^ state[i+5] ^ state[i+10] ^ state[i+15] ^ state[i+20];
//		}
//		for(i=0;i<5;i++)
//		{
//			temp_lane = temp_plane[(i+4)%5] ^ ROTL64(temp_plane[(i+1)%5],1);
//			for(j=0;j<25;j+=5)
//				state[j+i]^=temp_lane;
//		}
//	
//	//Implementation 2: 655 states : 16% Code
//	/*
//	temp_plane[0] = state[0] ^ state[5] ^ state[10] ^ state[15] ^ state[20];
//	temp_plane[1] = state[1] ^ state[6] ^ state[11] ^ state[16] ^ state[21];
//	temp_plane[2] = state[2] ^ state[7] ^ state[12] ^ state[17] ^ state[22];
//	temp_plane[3] = state[3] ^ state[8] ^ state[13] ^ state[18] ^ state[23];
//	temp_plane[4] = state[4] ^ state[9] ^ state[14] ^ state[19] ^ state[24];

//	st1[0]=state[0] ^ temp_plane[4] ^ ROTL64(temp_plane[1],1);
//	st1[1]=state[1] ^ temp_plane[0] ^ ROTL64(temp_plane[2],1);
//	st1[2]=state[2] ^ temp_plane[1] ^ ROTL64(temp_plane[3],1);
//	st1[3]=state[3] ^ temp_plane[2] ^ ROTL64(temp_plane[4],1);
//	st1[4]=state[4] ^ temp_plane[3] ^ ROTL64(temp_plane[0],1);
//	st1[5]=state[5] ^ temp_plane[4] ^ ROTL64(temp_plane[1],1);
//	st1[6]=state[6] ^ temp_plane[0] ^ ROTL64(temp_plane[2],1);
//	st1[7]=state[7] ^ temp_plane[1] ^ ROTL64(temp_plane[3],1);
//	st1[8]=state[8] ^ temp_plane[2] ^ ROTL64(temp_plane[4],1);
//	st1[9]=state[9] ^ temp_plane[3] ^ ROTL64(temp_plane[0],1);
//	st1[10]=state[10] ^ temp_plane[4] ^ ROTL64(temp_plane[1],1);
//	st1[11]=state[11] ^ temp_plane[0] ^ ROTL64(temp_plane[2],1);
//	st1[12]=state[12] ^ temp_plane[1] ^ ROTL64(temp_plane[3],1);
//	st1[13]=state[13] ^ temp_plane[2] ^ ROTL64(temp_plane[4],1);
//	st1[14]=state[14] ^ temp_plane[3] ^ ROTL64(temp_plane[0],1);
//	st1[15]=state[15] ^ temp_plane[4] ^ ROTL64(temp_plane[1],1);
//	st1[16]=state[16] ^ temp_plane[0] ^ ROTL64(temp_plane[2],1);
//	st1[17]=state[17] ^ temp_plane[1] ^ ROTL64(temp_plane[3],1);
//	st1[18]=state[18] ^ temp_plane[2] ^ ROTL64(temp_plane[4],1);
//	st1[19]=state[19] ^ temp_plane[3] ^ ROTL64(temp_plane[0],1);
//	st1[20]=state[20] ^ temp_plane[4] ^ ROTL64(temp_plane[1],1);
//	st1[21]=state[21] ^ temp_plane[0] ^ ROTL64(temp_plane[2],1);
//	st1[22]=state[22] ^ temp_plane[1] ^ ROTL64(temp_plane[3],1);
//	st1[23]=state[23] ^ temp_plane[2] ^ ROTL64(temp_plane[4],1);
//	st1[24]=state[24] ^ temp_plane[3] ^ ROTL64(temp_plane[0],1);
//	*/
//	
//	//rho and pi
//	//Implementation 1: 
//	        temp_lane = state[1];
//        for (i = 0; i < 24; i++) {
//            j = pi_lane_const[i];
//            temp_plane[0] = state[j];
//            state[j] = ROTL64(temp_lane, rho_rot_const[i]);
//            temp_lane = temp_plane[0];
//        }
//	
//	//Implementation 2:
//	
//	//chi
//	
//	//iota
//		state[0]^=iota_rnd_const[round];

//}
///*
//uint32_t* keccak_pad(const uint32_t *in, unsigned long inlen)
//{
//	return state;
//}
//*/
