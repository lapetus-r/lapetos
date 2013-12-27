/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃			  														  lapetOS			   													   ┃
┃				 						 [ General Purpose Kernel for Embedded System ]									   ┃
┃			  																   																	   ┃
┃			  							  					SangMyung University									   					   ┃
┃			  							  				  Computer Science Major												       ┃
┃			  																				   													   ┃
┃					  					  Made By: Yoo Sang-Gi / Park Il-Kwon, 2011-2012							  	   ┃
┃			  											 	 File Name: serial.h 											   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

#ifndef _SERIAL_HEADER_
#define _SERIAL_HEADER_

typedef enum 
{ 
    BAUD_110    =      110,
    BAUD_300    =      300,
    BAUD_600    =      600,
    BAUD_1200   =     1200,
    BAUD_2400   =     2400,
    BAUD_4800   =     4800,
    BAUD_9600   =     9600,
    BAUD_14400  =    14400,
    BAUD_19200  =    19200,
    BAUD_38400  =    38400,
    BAUD_57600  =    57600,
    BAUD_115200 =   115200,
    BAUD_230400 =   230400
} eBauds;

extern void SerialInit( eBauds baudrate);		// 메인 시리얼 초기화 
extern void SerialOutChar( const char c  );    	// 시리얼에 한 문자를 출력한다. 
extern int  SerialOutStr( char *str, int size );	// 시리얼에 버퍼의 내용을 출력한다. 
extern void SerialOutChar_CheckCR( const char c  );    // 시리얼에 한 문자를 출력한다. 
extern int  SerialOutStr_CheckCR( char *str, int size ); // 시리얼에 버퍼의 내용을 출력한다. 

extern int SerialIsReadyChar( void );
extern char SerialIsGetChar( void );
extern char SerialIsClearError( void );
extern int SerialIsGetError( void );

#endif //_SERIAL_HEADER_

