
//#include "quark.h"
//#pragma import(__use_realtime_heap)

////defining the lengths in bytes
////b=r+c ; b=136 bits , r=8 bits and c=128 bits

///* 48 bytes */
//u8 iv[] = {0x3b,0x45,0x03,0xec,0x76,0x62,0xc3,0xcb,
//	   0x30,0xe0,0x08,0x37,0xec,0x8d,0x38,0xbb,
//	   0xe5,0xff,0x5a,0xcd,0x69,0x01,0xa2,0x49,
//	   0x57,0x50,0xf9,0x19,0x8e,0x2e,0x3b,0x58,
//	   0x52,0xdc,0xaa,0x16,0x62,0xb7,0xda,0xd6,
//	   0x5f,0xcb,0x5a,0x8a,0x1f,0x0d,0x5f,0xcc};
//	   
//		 
//int permute_c( u32 * x ) 
//{  
//  u32 X[(N_LEN_C+ROUNDS_C)*sizeof(u32)], Y[(N_LEN_C+ROUNDS_C)*sizeof(u32)], L[(N_LEN_C+ROUNDS_C)*sizeof(u32)];
//  u32 h;
//  int i;

//  //X = (u32*)malloc((N_LEN_C+ROUNDS_C)*sizeof(u32));
//  //Y = (u32*)malloc((N_LEN_C+ROUNDS_C)*sizeof(u32));
//  //L = (u32*)malloc((L_LEN_C+ROUNDS_C)*sizeof(u32));

//  /* local copy of the state in the registers*/
//  for(i=0; i< N_LEN_C; ++i) 
//	{
//    X[i]=x[i];
//    Y[i]=x[i+N_LEN_C];
//  }

//  /* initialize the LFSR to 11..11 */
//  for(i=0; i< L_LEN_C; ++i)   
//    L[i]=0xFFFFFFFF;

//  /* iterate rounds */
//  for(i=0; i< ROUNDS_C; ++i) {

//    X[N_LEN_C+i]  = X[i] ^ Y[i];
//    X[N_LEN_C+i] ^= X[i+13] ^ X[i+34] ^ X[i+65] ^ X[i+77] ^
//      X[i+94] ^ X[i+109] ^ X[i+127] ^ X[i+145] ^ X[i+157] ^ X[i+140] ^ 
//      ( X[i+159] & X[i+157] ) ^ ( X[i+109] & X[i+94] ) ^ ( X[i+47] & X[i+13] ) ^
//      ( X[i+157] & X[i+145] & X[i+127] ) ^ (X[i+94] & X[i+77] & X[i+65] ) ^
//      ( X[i+159] & X[i+127] & X[i+77] & X[i+13] ) ^
//      ( X[i+157] & X[i+145] & X[i+109] & X[i+94] ) ^
//      ( X[i+159] & X[i+157] & X[i+65] & X[i+47] ) ^
//      ( X[i+159] & X[i+157] & X[i+145] & X[i+127] & X[i+109] ) ^
//      ( X[i+94] & X[i+77] & X[i+65] & X[i+47] & X[i+13] ) ^
//      ( X[i+145] & X[i+127] & X[i+109] & X[i+94] & X[i+77] & X[i+65] );

//    Y[N_LEN_C+i]  = Y[i];
//    Y[N_LEN_C+i] ^= Y[i+21] ^ Y[i+57] ^ Y[i+60] ^ Y[i+94] ^
//      Y[i+112]  ^ Y[i+125] ^ Y[i+133] ^ Y[i+152] ^ Y[i+157] ^  Y[i+146] ^ 
//      ( Y[i+159] & Y[i+157] ) ^ ( Y[i+125] & Y[i+112] ) ^ ( Y[i+36] & Y[i+21] ) ^
//      ( Y[i+157] & Y[i+152] & Y[i+133] ) ^ (Y[i+112] & Y[i+94] & Y[i+60] ) ^
//      ( Y[i+159] & Y[i+133] & Y[i+94] & Y[i+21] ) ^
//      ( Y[i+157] & Y[i+152] & Y[i+125] & Y[i+112] ) ^
//      ( Y[i+159] & Y[i+157] & Y[i+60] & Y[i+36] ) ^
//      ( Y[i+159] & Y[i+157] & Y[i+152] & Y[i+133] & Y[i+125] ) ^
//      ( Y[i+112] & Y[i+94] & Y[i+60] & Y[i+36] & Y[i+21] ) ^
//      ( Y[i+152] & Y[i+133] & Y[i+125] & Y[i+112] & Y[i+94] & Y[i+60] );

//    L[L_LEN_C+i]  = L[i] ^ L[i+2] ^ L[i+3] ^ L[i+5];


//    h = X[i+25] ^ Y[i+59] ^ ( Y[i+3] & X[i+55] ) ^ (X[i+46] & X[i+55]) ^ (X[i+55] & Y[i+59]) ^
//      (Y[i+3] & X[i+25] & X[i+46] ) ^ (Y[i+3] & X[i+46] & X[i+55] ) ^ (Y[i+3] & X[i+46] & Y[i+59] ) ^
//      (X[i+25] & X[i+46] & Y[i+59] & L[i]) ^ (X[i+25] & L[i]);
//    h ^= L[i]; 
//    h ^= X[i+4] ^ X[i+28] ^ X[i+40] ^ X[i+85] ^ X[i+112] ^ X[i+141] ^ X[i+146] ^ X[i+152];
//    h ^= Y[i+2] ^ Y[i+33] ^ Y[i+60] ^ Y[i+62] ^ Y[i+ 87] ^ Y[i+ 99] ^ Y[i+138] ^ Y[i+148];

//    X[N_LEN_C+i] ^= h;
//    Y[N_LEN_C+i] ^= h;
//  }

//  /* copy final state into hashState */
//  for(i=0; i< N_LEN_C; ++i) {
//    x[i] = X[ROUNDS_C+i];
//    x[i+N_LEN_C] = Y[ROUNDS_C+i];
//  }

//  free(X);
//  free(Y);
//  free(L);
//  
//  return 0;
//}



///* initialization of the IV */
//int init(hashState *state)
//{
//  int i;

//  /* initialize state */
//  for (i = 0;i < 8*WIDTH;++i) 
//    state->x[i] = (iv[i/8]>>(7-(i%8)))&1;

//  state->pos = 0;
//  return 0;
//}


//int update(hashState *state, const u8 *data, int databytelen)
//{
//  /* caller promises us that previous data had integral number of bytes */
//  /* so state->pos is a multiple of 8 */

//  int i;
//  while (databytelen > 0) 
//	{
//    /* get next byte */
//    u8 u = *data;    

//    /* xor state with each bit */
//    for(i=8*state->pos;i<8*state->pos+8;++i) {
//      state->x[(8*(WIDTH-RATE))+i] ^= (u>>(i%8))&1;
//    }

//    data += 1;
//    databytelen -= 1;
//    state->pos += 1;

//    if (state->pos == RATE) 
//		{
//      permute_c(state->x);
//      state->pos = 0;
//    }
//  }
//  return 0;
//}


///* finalize (padding) and return digest */
//int final(hashState *state, u8 *out)
//{
//  int i;
//  int outbytes=0;
//  u8 u;

//  /* append '1' bit */
//    state->x[8*(WIDTH-RATE)+state->pos*8] ^= 1;

//  /* permute to obtain first final state*/
//  permute_c(state->x);

//  /* zeroize output buffer */
//  for(i=0;i<DIGEST;++i)
//    out[i]=0;

//  /* while output requested, extract RATE bytes and permute */
//  while (outbytes < DIGEST ) {
//    
//    /* extract one byte */
//    for(i=0;i<8;++i) {
//      u = state->x[8*(WIDTH-RATE)+i+8*(outbytes%RATE)] &1;
//      out[outbytes] ^= (u << (7-i));
//    }
//    outbytes += 1;
//    
//    if (outbytes == DIGEST )
//      break;

//    /* if RATE bytes extracted, permute again */
//    if ( ! ( outbytes % RATE ) ) {
//      permute_c(state->x);
//    }
//  }


//  return 0;
//}



//int quark(u8 *out, const u8 *in, u64 inlen) {
//  /* inlen in bytes */

//  hashState state;

//  init(&state);
//  update(&state, in, inlen);
//  final(&state, out);

//  return 0;
//}


///*
//int main() {

//#define LEN 64 // length of the data to hash
//  u8 data[LEN], out[DIGEST];
//  int i;

//   u8 digest_empty[] = {0x1c,0xb9,0x77,0x0e,0xe7,0xc2,0x5f,0xa9,
//		       0xdc,0xe2,0xc9,0x46,0x45,0x78,0x33,0x7c,
//		       0x69,0xc7,0xe2,0x6c,0xb4,0xf1,0xbd,0xf4,
//		       0x48,0x69,0xf1,0xa9,0x36,0x39,0xf1,0xf3,
//		       0x60,0xb8,0x88,0x97,0x5f,0xf9,0xff,0xee,
//		       0x88,0x0d,0x2c,0x49,0x91,0x08,0xa2,0x7a};

//  printf("c-Quark: c=%d r=%d b=%d n=%d\n", CAPACITY, RATE, WIDTH, DIGEST);

//  /* hash the empty string */
///*
//  quark( out, data, 0);

//  for(i=0;i<DIGEST;++i)
//    printf("%02x",out[i]);
//  printf("\n");

//  /* digests of empty messages (ie, process blocs 0x80, 0x8000,
//     0x80000000, 0x8000000000000000) */
//	/*
//  for(i=0;i<DIGEST;++i) 
//    if (out[i]!=digest_empty[i]) { printf("error\n");return 0; }
//  printf("ok\n");
//  
//  return 0;
//}
//*/