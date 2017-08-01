// UART.c
// Runs on TM4C123 or LM4F120
// Lab 11 involves switching this from UART1 to UART0.
//                 switching from PC5,PC4 to PA1,PA0
// Daniel Valvano
// August 3, 2013

/* This example accompanies the book
   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2013

 Copyright 2013 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// this connection occurs in the USB debugging cable
// U0Rx (PA0) connected to serial port on PC
// U0Tx (PA1) connected to serial port on PC
// Ground connected ground in the USB cable

#include "tm4c123gh6pm.h"
#include "UART.h"
#include<stdio.h>

#define BUFF_SIZE 200

char buffer[BUFF_SIZE];
char *p;

void setColour(unsigned long c)
{
	if(c==1)
		GPIO_PORTF_DATA_R = 0x08;
	else if(c==0)
		GPIO_PORTF_DATA_R = 0x02;
}

void PortF_Init(void)
{ 
	volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     // 1) F clock
  delay = SYSCTL_RCGC2_R;           // delay   
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0  
  GPIO_PORTF_CR_R |= 0x1F;           // allow changes to PF4-0       
  GPIO_PORTF_AMSEL_R &= 0x00;        // 3) disable analog function
  GPIO_PORTF_PCTL_R &= 0x00000000;   // 4) GPIO clear bit PCTL  
  GPIO_PORTF_DIR_R &= ~0x11;          // 5.1) PF4,PF0 input, 
  GPIO_PORTF_DIR_R |= 0x0E;          // 5.2) PF3 output  
  GPIO_PORTF_AFSEL_R &= 0x00;        // 6) no alternate function
  GPIO_PORTF_PUR_R |= 0x11;          // enable pullup resistors on PF4,PF0       
  GPIO_PORTF_DEN_R |= 0x1F;          // 7) enable digital pins PF4-PF0     
}

//------------UART_Init------------
// Initialize the UART for 115200 baud rate (assuming 80 MHz UART clock),
// 8 bit word length, no parity bits, one stop bit, FIFOs enabled
// Input: none
// Output: none

void UART_Init(void){
// as part of Lab 11, modify this program to use UART0 instead of UART1
//                 switching from PC5,PC4 to PA1,PA0
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART0; // activate UART0 (0x00000001)
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA; // activate port A (0x00000001)
  UART0_CTL_R &= ~UART_CTL_UARTEN;      // disable UART (~0x00000001)
  //For 115200 bits/sec
	//UART0_IBRD_R = 43;                    // IBRD = int(80,000,000 / (16 * 115200)) = int(43.402778)
  //UART0_FBRD_R = 26;                    // FBRD = round(0.402778 * 64) = 26
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
	
	//For 9600 bits/sec
	UART0_IBRD_R = 520;                    // IBRD = int(80,000,000 / (16 * 9600)) = int(520.83333)
  UART0_FBRD_R = 53;                    // FBRD = round(0.83333 * 64) = 53
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
	
  UART0_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN); //0x00000006|0x00000001 -> 8bit, no parity bits, 1 stop, FIFOs
  UART0_CTL_R |= UART_CTL_UARTEN;       // enable UART
  GPIO_PORTA_AFSEL_R |= 0x03;           // enable alt funct on PA1,PA0
  GPIO_PORTA_DEN_R |= 0x03;             // enable digital I/O on PA1,PA0
                                        // configure PA1,PA0 as UART0
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)+0x00000011;		//PCTL 0-1 set to 0x11 on PA1(U1Tx) and PA0(U1Rx)
																				//PCTL 4-5 set to 0x22 on PC5(U1Tx) and PC4(U1Rx)
  GPIO_PORTA_AMSEL_R &= ~0x03;          // disable analog functionality on PA1,PA0
}


//For UART1, PC4-Rx and PC5-Tx
/*
void UART_Init(void){
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART1; // activate UART1
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOC; // activate port C
  UART1_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
  UART1_IBRD_R = 520;  // 80,000,000/(16*9600)) = 43.40278
  UART1_FBRD_R = 53;  //6-bbit fraction, round(0.40278 * 64) = 26
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART1_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART1_CTL_R |= UART_CTL_UARTEN;       // enable UART
  GPIO_PORTC_AFSEL_R |= 0x30;           // enable alt funct on PC5-4
  GPIO_PORTC_DEN_R |= 0x30;             // enable digital I/O on PC5-4
                                        // configure PC5-4 as UART1
  GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFF00FFFF)+0x00220000;
  GPIO_PORTC_AMSEL_R &= ~0x30;          // disable analog functionality on PC5-4
}
*/


//------------UART_InChar------------
// Wait for new serial port input
// Input: none
// Output: ASCII code for key typed

unsigned char UART_InChar(void)
{
  while((UART0_FR_R&UART_FR_RXFE) != 0);		//UART0_FR_R&0x0010 -> wait for new data
  return((unsigned char)(UART0_DR_R&0xFF));
}

//For UART1
/*
unsigned char UART_InChar(void)
{
  while((UART1_FR_R&UART_FR_RXFE) != 0);		//UART0_FR_R&0x0010 -> wait for new data
  return((unsigned char)(UART1_DR_R&0xFF));
}
*/


//------------UART_InCharNonBlocking------------
// Get oldest serial port input and return immediately
// if there is no data.
// Input: none
// Output: ASCII code for key typed or 0 if no character

unsigned char UART_InCharNonBlocking(void){
// as part of Lab 11, modify this program to use UART0 instead of UART1
  if((UART0_FR_R&UART_FR_RXFE) == 0){
    return((unsigned char)(UART0_DR_R&0xFF));
  } else{
    return 0;
  }
}

/*
//For UART1
unsigned char UART_InCharNonBlocking(void){
// as part of Lab 11, modify this program to use UART0 instead of UART1
  if((UART1_FR_R&UART_FR_RXFE) == 0){
    return((unsigned char)(UART1_DR_R&0xFF));
  } else{
    return 0;
  }
}
*/

//------------UART_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none

void UART_OutChar(unsigned char data){
// as part of Lab 11, modify this program to use UART0 instead of UART1
  while((UART0_FR_R&UART_FR_TXFF) != 0);
  UART0_DR_R = data;
}


/*
//For UART1
void UART_OutChar(unsigned char data){
// as part of Lab 11, modify this program to use UART0 instead of UART1
  while((UART1_FR_R&UART_FR_TXFF) != 0);
  UART1_DR_R = data;
}
*/

//------------UART_InUDec------------
// InUDec accepts ASCII input in unsigned decimal format
//     and converts to a 32-bit unsigned number
//     valid range is 0 to 4294967295 (2^32-1)
// Input: none
// Output: 32-bit unsigned number
// If you enter a number above 4294967295, it will return an incorrect value
// Backspace will remove last digit typed
unsigned long UART_InUDec(void)
{
	unsigned long number=0, length=0;
	char character;
  character = UART_InChar();
  while(character != CR){ // accepts until <enter> is typed
	// The next line checks that the input is a digit, 0-9.
	// If the character is not 0-9, it is ignored and not echoed
    if((character>='0') && (character<='9')) {
      number = 10*number+(character-'0');   // this line overflows if above 4294967295
      length++;
      UART_OutChar(character);
    }
	// If the input is a backspace, then the return number is
	// changed and a backspace is outputted to the screen
    else if((character==BS) && length){
      number /= 10;
      length--;
      UART_OutChar(character);
    }
    character = UART_InChar();
  }
  return number;
}

//------------UART_InString------------
// Input String (NULL termination)
// Input: pointer to a NULL-terminated string to be transferred
// Output: Echoed Input String 
char* UART_InString()
{
	unsigned long length=0;
	char character;
	p=buffer;
  character = UART_InChar();
  while(character != CR) 	//while ENTER is not pressed and length < 512 
	{
		if(character==BS)
		{
      //length--;
      UART_OutChar(character);
			UART_OutChar(0x20);
			UART_OutChar(character);
    }
		else
		{
			*p=character;
      //length++;
			p++;
      UART_OutChar(character);
		}
	  
    character = UART_InChar();
  }
	*p=0x00;
	//UART_OutString(buffer);
  return buffer;
}

//------------UART_OutString------------
// Output String (NULL termination)
// Input: pointer to a NULL-terminated string to be transferred
// Output: none
void UART_OutString(unsigned char buffer[])
{
	while(*buffer)
	{
		UART_OutChar(*buffer);
		buffer++;
	}
}

unsigned char String[11];
//-----------------------UART_ConvertUDec-----------------------
// Converts a 32-bit number in unsigned decimal format
// Input: 32-bit number to be transferred
// Output: store the conversion in global variable String[10]
// Fixed format max 10 digits, one space after, null termination
void UART_ConvertUDec(unsigned long n)
{
	unsigned char stack[11];
	long count=0, top=-1, begFlag=0;

		while(n!=0 && count<10)
		{
			stack[++top] = n%10 + 0x30;
			n=n/10;
			count++;
		}
  
		while(count>0)
		{
			String[begFlag++] = stack[top--];
			count--;
		}
		String[begFlag++]=0x20;  //space
		String[begFlag++]=0x00;  //null
	
}

//-----------------------UART_OutUDec-----------------------
// Output a 32-bit number in unsigned decimal format
// Input: 32-bit number to be transferred
// Output: none
void UART_OutUDec(unsigned long n)
{
  UART_ConvertUDec(n);     // convert using function
  UART_OutString(String);  
}

void UART_OutHashHex(unsigned char md[64], unsigned long hash_len)
{
	//store the character form of md in 64*2 char array
	
	unsigned long i=0;
	unsigned char l_nibble, r_nibble;
	while(i<hash_len)
	{
		//UART_OutChar('0');
		//UART_OutChar('x');
		r_nibble = 0x0F & md[i];		//right 4 bits of char
		l_nibble = 0xF0 & md[i++];
		l_nibble >>= 4;
		
		//UART_OutUDec((unsigned long)l_nibble);
		//UART_OutUDec((unsigned long)r_nibble);
		
		if(l_nibble <= 0x09)
			UART_OutChar(l_nibble+0x30);		//output char 0-9
		else
			UART_OutChar(l_nibble+0x37);		//output char A-F
		
		if(r_nibble <= 0x09)
			UART_OutChar(r_nibble+0x30);
		else
			UART_OutChar(r_nibble+0x37);
		
		UART_OutChar(0x20);			//output space
	}
}

/*
// Print a character to UART0.
int fputc(int ch, FILE *f)
{
  if((ch == 10) || (ch == 13) || (ch == 27)){
    UART_OutChar(13);
    UART_OutChar(10);
    return 1;
  }
  UART_OutChar(ch);
  return 1;
}
// input from UART, return data.
int fgetc(FILE *f)
{
	char ch;
	ch = UART_InChar();
	UART_OutChar(ch);
  return ch;
}
// Function called when file error occurs.
int ferror(FILE *f){
  // Your implementation of ferror 
  return EOF;
}
*/
