/*
����������������������������������������������������������������������������������������������
��			  														  lapetOS			   													   ��
��				 						 [ General Purpose Kernel for Embedded System ]									   ��
��			  																   																	   ��
��			  							  					SangMyung University									   					   ��
��			  							  				  Computer Science Major												       ��
��			  																				   													   ��
��					  					  Made by: Yoo Sang-Gi / Park Il-Kwon, 2011-2012							  	   ��
��			  											 	   File Name: serial.c		 												   ��
����������������������������������������������������������������������������������������������
*/

#include <serial.h>
#include <stdio.h>
#include <s3c2440.h>
#include <time.h>

static int SerialErrorFlag = 0;

static volatile Word *UART = UART2_BASE; // UART ���̽� ��巹�� 

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

// ���� : �ø��� ����̽��� �� ���ڸ� ������. 

void SerialOutChar( const char c  )
{
	// ���� �����Ҷ����� ��ٸ���. 
	//Wait until THR is empty.
	while(!(UART_TRxSTAT & UTRxSTAT_TX_EMPTY)) ;

	// �ø��� ����Ÿ�� ����Ѵ�. 
	UART_TXD = c;
}

// ���� : �ø��� ����̽��� �� ���ڸ� ������. 

void SerialOutChar_CheckCR( const char c  )
{
	SerialOutChar( c );
	if(c == '\n') SerialOutChar('\r');
}

// ���� : �ø��� ����̽��� ���ڿ��� ������. 

int SerialOutStr( char *str, int size )
{
	int	lp ;

	for (lp=0;lp<size;lp++) SerialOutChar(str[lp]) ;

	return lp;
}

// ���� : �ø��� ����̽��� ���ڿ��� ������. 

int SerialOutStr_CheckCR( char *str, int size )
{
	int	lp ;

	for (lp=0;lp<size;lp++) SerialOutChar_CheckCR(str[lp]) ;

	return lp;
}

// ���� : �ø��� ����̽����� ���ŵ� ����Ÿ�� �ִ��� Ȯ���Ѵ�. 

int SerialIsReadyChar( void )
{
	// ���ŵ� ����Ÿ�� �ִ°��� Ȯ���Ѵ�. 	
	if( UART_TRxSTAT & UTRxSTAT_RX_BUFF_REAYD) return 1;
	return 0;
}

// ���� : �ø��� ����̽����� ����Ÿ�� �о� �´�. 

char SerialIsGetChar( void )
{
    char RxData;
        
    // ���ŵ� ����Ÿ�� ���� �´�. 
    RxData =  (char) UART_RXD;
	
	// ������ ���� �´�. 
	SerialErrorFlag = UART_ERRSTAT & 0xF;
	
	return RxData;
}

// ���� : �ø��� ����̽��� ���� ���� �ö�׸� Ŭ���� �Ѵ�. 

char SerialIsClearError( void )
{
	SerialErrorFlag = 0;
	return (char)SerialErrorFlag;
}

// ���� : �ø��� ����̽��� ���� ���� �ö�� ���� ��´�. 

int SerialIsGetError( void )
{
	return SerialErrorFlag;
}

