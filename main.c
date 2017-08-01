// main.c
// Runs on LM4F120/TM4C123
// April 8, 2014

// this connection occurs in the USB debugging cable
// U0Rx (PA0) connected to serial port on PC
// U0Tx (PA1) connected to serial port on PC
// Ground connected ground in the USB cable

#include<string.h>
#include<stdint.h>
#include "UART.h"
#include "keccak.h"
#include "SysTick.h"
#include "TExaS.h"
//#include "quark.h"
//#include "myKeccak.h"
/*
typedef struct
{
	unsigned long mdlen;
	char *msgstr;
	uint8_t md[64];
}test_triplet_t;
*/
//void EnableInterrupts(void);  // Enable interrupts
//char *msg="Keccak-512 Test Hash";
char *msgstr=" ";
//volatile unsigned long test[10]={0,1,2,3,4,5,6,7,8,9};

uint8_t md[64];
char *data="";
int main(void)
{
		//char *msg="Digital Signature Scheme using RSA and SHA-3 Keccak-512 Test Hash Digital Signature Scheme using RSA and SHA-3 Keccak-512 Test Hash";
		unsigned long c=0;
	//unsigned long n;
  TExaS_Init();             // initialize grader, set system clock to 80 MHz
  UART_Init();              // initialize UART
	PortF_Init();
	
	//in_value.msgstr="Keccak-512 Test Hash";
  //UART_OutString("Digital Signature Scheme using RSA and SHA-3(Keccak)");
	
	while(1)
	{
		
		//UART_OutString("\n\rInput: ");
		msgstr=UART_InString();		//n is the length of the string
		////UART_OutString("\n\rInput Msg : ");
		//UART_OutString((unsigned char *)msgstr);
		////UART_OutString(msg);
		
		//UART_OutString("\n\rMessage Length = ");
		
		//UART_OutUDec(strlen(in_value.msgstr));
		
		
		/*
		if(c==0 && keccak_test()==0)
		{
			UART_OutString("\n\rKeccak self-test OK!");
			c++;
		}
		*/
		
		
		//calling the keccak function for KECCAK-1600 computation.
		c=(c+1)%8;
		//setColour(c);
		
		keccak((uint8_t *)msgstr, strlen(msgstr), md, 64);
		//c=quark(md, data, 0);
		//keccak_f((uint32_t *)msgstr, strlen(msgstr), (uint32_t *)md, 64);
		setColour(c);
		
		
		//UART_OutString("\n\rMsg String: ");
		//UART_OutString(in_value.msgstr);
    UART_OutString("\n\r");
		
		
		//UART_OutString(in_value.msgstr);
		//UART_OutString(in_value.md);
		
		UART_OutHashHex(md, 64);
		
		//Input arbitrary length data.
		/*
		n = UART_InUDec();
		UART_OutString(" UART_OutUDec = ");
		UART_OutUDec(n);     // your function
		UART_OutString(",  UART_OutDistance ~ ");
		*/
		
	}
}

	/*	
	u8 data[64], out[DIGEST];
				
	  u8 digest_empty[] = {0x1c,0xb9,0x77,0x0e,0xe7,0xc2,0x5f,0xa9,
		       0xdc,0xe2,0xc9,0x46,0x45,0x78,0x33,0x7c,
		       0x69,0xc7,0xe2,0x6c,0xb4,0xf1,0xbd,0xf4,
		       0x48,0x69,0xf1,0xa9,0x36,0x39,0xf1,0xf3,
		       0x60,0xb8,0x88,0x97,0x5f,0xf9,0xff,0xee,
		       0x88,0x0d,0x2c,0x49,0x91,0x08,0xa2,0x7a};

	test_triplet_t in_value = {
            64, "Keccak-512 Test Hash", {                
								0x96, 0xEE, 0x47, 0x18, 0xDC, 0xBA, 0x3C, 0x74, 
                0x61, 0x9B, 0xA1, 0xFA, 0x7F, 0x57, 0xDF, 0xE7, 
                0x76, 0x9D, 0x3F, 0x66, 0x98, 0xA8, 0xB3, 0x3F, 
                0xA1, 0x01, 0x83, 0x89, 0x70, 0xA1, 0x31, 0xE6, 
                0x21, 0xCC, 0xFD, 0x05, 0xFE, 0xFF, 0xBC, 0x11, 
                0x80, 0xF2, 0x63, 0xC2, 0x7F, 0x1A, 0xDA, 0xB4, 
                0x60, 0x95, 0xD6, 0xF1, 0x25, 0x33, 0x14, 0x72, 
                0x4B, 0x5C, 0xBF, 0x78, 0x28, 0x65, 0x8E, 0x6A 
						}
        };
	*/

//unsigned long keccak_test()
//{
//	test_triplet_t testvec[4] = {   
//        {
//            28, "Keccak-224 Test Hash", {
//                0x30, 0x04, 0x5B, 0x34, 0x94, 0x6E, 0x1B, 0x2E, 
//                0x09, 0x16, 0x13, 0x36, 0x2F, 0xD2, 0x2A, 0xA0, 
//                0x8E, 0x2B, 0xEA, 0xFE, 0xC5, 0xE8, 0xDA, 0xEE, 
//                0x42, 0xC2, 0xE6, 0x65 }
//        }, {
//            32, "Keccak-256 Test Hash", {
//                0xA8, 0xD7, 0x1B, 0x07, 0xF4, 0xAF, 0x26, 0xA4, 
//                0xFF, 0x21, 0x02, 0x7F, 0x62, 0xFF, 0x60, 0x26, 
//                0x7F, 0xF9, 0x55, 0xC9, 0x63, 0xF0, 0x42, 0xC4, 
//                0x6D, 0xA5, 0x2E, 0xE3, 0xCF, 0xAF, 0x3D, 0x3C }
//        }, {
//            48, "Keccak-384 Test Hash", {
//                0xE2, 0x13, 0xFD, 0x74, 0xAF, 0x0C, 0x5F, 0xF9, 
//                0x1B, 0x42, 0x3C, 0x8B, 0xCE, 0xEC, 0xD7, 0x01, 
//                0xF8, 0xDD, 0x64, 0xEC, 0x18, 0xFD, 0x6F, 0x92, 
//                0x60, 0xFC, 0x9E, 0xC1, 0xED, 0xBD, 0x22, 0x30, 
//                0xA6, 0x90, 0x86, 0x65, 0xBC, 0xD9, 0xFB, 0xF4, 
//                0x1A, 0x99, 0xA1, 0x8A, 0x7D, 0x9E, 0x44, 0x6E }
//        }, {
//            64, "Keccak-512 Test Hash", {
//                0x96, 0xEE, 0x47, 0x18, 0xDC, 0xBA, 0x3C, 0x74, 
//                0x61, 0x9B, 0xA1, 0xFA, 0x7F, 0x57, 0xDF, 0xE7, 
//                0x76, 0x9D, 0x3F, 0x66, 0x98, 0xA8, 0xB3, 0x3F, 
//                0xA1, 0x01, 0x83, 0x89, 0x70, 0xA1, 0x31, 0xE6, 
//                0x21, 0xCC, 0xFD, 0x05, 0xFE, 0xFF, 0xBC, 0x11, 
//                0x80, 0xF2, 0x63, 0xC2, 0x7F, 0x1A, 0xDA, 0xB4, 
//                0x60, 0x95, 0xD6, 0xF1, 0x25, 0x33, 0x14, 0x72, 
//                0x4B, 0x5C, 0xBF, 0x78, 0x28, 0x65, 0x8E, 0x6A }
//        }
//    };
//	uint8_t i, fails;
//	uint8_t md[64];

//	fails=0;
//	for(i=0;i<4;i++)
//		{
//			UART_OutString(testvec[i].msgstr);
//			keccak((uint8_t *)testvec[i].msgstr, strlen(testvec[i].msgstr), md, testvec[i].mdlen);
//			
//			UART_OutString("\n\rInput Msg : ");
//			UART_OutString(testvec[i].msgstr);
//			UART_OutString("\n\rLength : ");
//			UART_OutUDec(strlen(testvec[i].msgstr));
//			UART_OutString("\n\rHash : ");
//			UART_OutHashHex(testvec[i].md, testvec[i].mdlen);
//			UART_OutString("\n\rHash Length : ");
//			UART_OutUDec(strlen(testvec[i].msgstr));
//			if(memcmp(md, testvec[i].md, testvec[i].mdlen))
//			{
//				fails++;
//				UART_OutString("\n\rKeccak comparison FAILED.");
//			}
//		}
//		return fails;
//		
//}
