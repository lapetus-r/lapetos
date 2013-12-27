/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃			  														  lapetOS			   													   ┃
┃				 						 [ General Purpose Kernel for Embedded System ]									   ┃
┃			  																   																	   ┃
┃			  							  					SangMyung University									   					   ┃
┃			  							  				  Computer Science Major												       ┃
┃			  																				   													   ┃
┃					  					  Made By: Yoo Sang-Gi / Park Il-Kwon, 2011-2012							  	   ┃
┃			  											 	 File Name: serial.c		 													   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

#include<include.h>

static int SerialErrorFlag = 0;

//static volatile Word *UART = UART2_BASE; // UART 베이스 어드레스 

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

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃					 											 [ SerialOutChar ]														   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/
void SerialOutChar( const char ch  )					/* 시리얼 디바이스에 한 문자를 보냄 */
{
while(!(UTRSTAT1 &  0x2));
	UTXH1 = (char)ch;
}

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃							 								 [ SerialOutChar_CheckCR ]												   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/
void SerialOutChar_CheckCR( const char c  ) 	/* 시리얼 디바이스에 한 문자를 보냄. CR 의 LR CR 로 변경 출력 */ 
{
	SerialOutChar( c );
	if(c == '\n') SerialOutChar('\r');
}

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃					 						 				 [ SerialOutStr ]																   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/
int SerialOutStr( char *str, int size )					/* 시리얼 디바이스에 문자열을 보냄 */
{
	int	lp ;
	for (lp=0;lp<size;lp++) SerialOutChar(str[lp]) ;

	return lp;
}

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃					 												 [ printf ]																   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/
int SerialOutStr_CheckCR( char *str, int size )	/* 시리얼 디바이스에 문자열을 보낸다. */
{
	int	lp ;
	for (lp=0;lp<size;lp++) SerialOutChar_CheckCR(str[lp]) ;

	return lp;
}

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃					 												 [ printf ]																   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/
int SerialIsReadyChar( void )								/* 시리얼 디바이스에서 수신된 데이타가 있는지 확인 */
{
	if( !(UTRSTAT1 & 0x2)) return 1;
	return 0;
}

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃					 												 [ printf ]																   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/
unsigned int SerialIsGetChar( void )					/* 시리얼 디바이스에서 데이터를 읽음 */
{
    unsigned int RxData;
	
	while(!(UTRSTAT1 & 0x1));
	RxData = URXH1;

	return RxData;
}

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃					 												 [ printf ]																   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/
char SerialIsClearError( void )								/* 시리얼 디바이스 수신에러 플러그 클리어 */
{
	SerialErrorFlag = 0;
	return (char)SerialErrorFlag;
}

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃					 												 [ printf ]																   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/
int SerialIsGetError( void )									/* 시리얼 디바이스의 수신에러 플러그 값을 소유 */
{
	return SerialErrorFlag;
}

