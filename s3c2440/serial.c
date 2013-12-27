/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃			  														  lapetOS			   													   ┃
┃				 						 [ General Purpose Kernel for Embedded System ]									   ┃
┃			  																   																	   ┃
┃			  							  					SangMyung University									   					   ┃
┃			  							  				  Computer Science Major												       ┃
┃			  																				   													   ┃
┃					  					  Made by: Yoo Sang-Gi / Park Il-Kwon, 2011-2012							  	   ┃
┃			  											 	   File Name: serial.c		 												   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

#include <serial.h>
#include <stdio.h>
#include <s3c2440.h>
#include <time.h>

static int SerialErrorFlag = 0;

static volatile Word *UART = UART2_BASE; // UART 베이스 어드레스 

#define UART_LCR		((volatile Word) UART[ 0])  		//  UART line control register 
#define UART_UCR		((volatile Word) UART[ 1])  		//  UART control register
#define UART_FCR		((volatile Word) UART[ 2])  		//  UART FIFO control register
#define UART_MCR		((volatile Word) UART[ 3])  		//  UART modem control register
#define UART_TRxSTAT	((volatile Word) UART[ 4])  		//  UART Tx/Rx status register
#define UART_ERRSTAT	((volatile Word) UART[ 5])  		//  UART Rx error status register
#define UART_FSR		((volatile Word) UART[ 6])  		//  UART FIFO status register
#define UART_MSR		((volatile Word) UART[ 7])  		//  UART modem status register
#ifdef	__BIG_ENDIAN
#define UART_TXD		((volatile Byte) ((&UART[ 8])+3))	//  UART transmit buffer register
#define UART_RXD		((volatile Byte) ((&UART[ 9])+3))	//  UART receive buffer register
#else
#define UART_TXD		((volatile Byte) UART[ 8])  		//  UART transmit buffer register
#define UART_RXD		((volatile Byte) UART[ 9])  		//  UART receive buffer register
#endif                                              		
#define UART_BAUD		((volatile Word) UART[10])  		//  Baud rate divisor register

// 설명 : 시리얼 디바이스에 한 문자를 보낸다. 

void SerialOutChar( const char c  )
{
	// 전송 가능할때까지 기다린다. 
	//Wait until THR is empty.
	while(!(UART_TRxSTAT & UTRxSTAT_TX_EMPTY)) ;

	// 시리얼에 데이타를 출력한다. 
	UART_TXD = c;
}

// 설명 : 시리얼 디바이스에 한 문자를 보낸다. 

void SerialOutChar_CheckCR( const char c  )
{
	SerialOutChar( c );
	if(c == '\n') SerialOutChar('\r');
}

// 설명 : 시리얼 디바이스에 문자열을 보낸다. 

int SerialOutStr( char *str, int size )
{
	int	lp ;

	for (lp=0;lp<size;lp++) SerialOutChar(str[lp]) ;

	return lp;
}

// 설명 : 시리얼 디바이스에 문자열을 보낸다. 

int SerialOutStr_CheckCR( char *str, int size )
{
	int	lp ;

	for (lp=0;lp<size;lp++) SerialOutChar_CheckCR(str[lp]) ;

	return lp;
}

// 설명 : 시리얼 디바이스에서 수신된 데이타가 있는지 확인한다. 

int SerialIsReadyChar( void )
{
	// 수신된 데이타가 있는가를 확인한다. 	
	if( UART_TRxSTAT & UTRxSTAT_RX_BUFF_REAYD) return 1;
	return 0;
}

// 설명 : 시리얼 디바이스에서 데이타를 읽어 온다. 

char SerialIsGetChar( void )
{
    char RxData;
        
    // 수신된 데이타를 가져 온다. 
    RxData =  (char) UART_RXD;
	
	// 에러를 가져 온다. 
	SerialErrorFlag = UART_ERRSTAT & 0xF;
	
	return RxData;
}

// 설명 : 시리얼 디바이스의 수신 에러 플라그를 클리어 한다. 

char SerialIsClearError( void )
{
	SerialErrorFlag = 0;
	return (char)SerialErrorFlag;
}

// 설명 : 시리얼 디바이스의 수신 에러 플라그 값을 얻는다. 

int SerialIsGetError( void )
{
	return SerialErrorFlag;
}

