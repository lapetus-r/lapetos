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

extern void SerialInit( eBauds baudrate);		// ���� �ø��� �ʱ�ȭ 
extern void SerialOutChar( const char ch  );    	// �ø��� �� ���ڸ� ����Ѵ�. 
extern int  SerialOutStr( char *str, int size );	// �ø��� ������ ������ ����Ѵ�. 
extern void SerialOutChar_CheckCR( const char c  );    // �ø��� �� ���ڸ� ����Ѵ�. 
extern int  SerialOutStr_CheckCR( char *str, int size ); // �ø��� ������ ������ ����Ѵ�. 
extern int SerialIsReadyChar( void );
extern unsigned int SerialIsGetChar( void );
extern char SerialIsClearError( void );
extern int SerialIsGetError( void );

#endif //_SERIAL_HEADER_
