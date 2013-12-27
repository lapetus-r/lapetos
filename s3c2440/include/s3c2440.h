/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃			  														  lapetOS			   													   ┃
┃				 						 [ General Purpose Kernel for Embedded System ]									   ┃
┃			  																   																	   ┃
┃			  							  					SangMyung University									   					   ┃
┃			  							  				  Computer Science Major												       ┃
┃			  																				   													   ┃
┃					  					  Made By: Yoo Sang-Gi / Park Il-Kwon, 2011-2012							  	   ┃
┃			  											 	 File Name: s3c2440.h		 											   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

#ifndef __S3C2440_H__
#define __S3C2440_H__

#define	FCLK					399650000
#define	HCLK					FCLK/3		// FCLK=399650000	HCLK=133216000
#define	PCLK					FCLK/6		// FCLK=399650000	PCLK= 66608000


//	기본 형에 대한 정의  

typedef unsigned char   		Byte;
typedef unsigned short  		Word16 ;
typedef unsigned int    		Word32 ;
typedef Word32          		Word ;
typedef Word            		Quad [4] ;
typedef void            		*Address ;
typedef void            		(*ExcpHndlr) (void) ;

typedef int INT;
typedef char CHAR;
typedef float FLOAT;
typedef double DOUBLE;
typedef long LONG;
typedef unsigned int INT_U;
typedef unsigned char CHAR_U;
typedef unsigned long LONG_U;
typedef float FLOAT_U;
typedef double DOUBLE_U;

typedef CHAR_U BOOLEAN;
typedef unsigned long STACK;


//	기본 데이타 처리 매크로 

#define UData(Data)				((unsigned int) (Data))
                            	
#define Fld(Size, Shft)			(((Size)    << 16) + (Shft))
                            	
#define FSize(Field)			( (Field)   >> 16)
#define FShft(Field)			( (Field) & 0x0000FFFF)
#define FMsk(Field)				(((UData(1) << FSize(Field)) - 1) << FShft(Field))
#define FAlnMsk(Field)			( (UData(1) << FSize(Field)) - 1)
#define F1stBit(Field)			(  UData(1) << FShft(Field))
                            	
#define io_p2v(PhAdd)			(PhAdd)
                            	
#define __REG(x)				(*((volatile Word *) io_p2v (x))) 
#define __REG_B(x)				(*((volatile Byte *) io_p2v (x))) 

#define __REG2(x,y)				(*(volatile Word *)((Word)&__REG(x) + (y)))


//	S3C2440 physical 

#define S3C2440_CS0_PHYS		0x00000000
#define S3C2440_CS1_PHYS		0x08000000
#define S3C2440_CS2_PHYS		0x10000000
#define S3C2440_CS3_PHYS		0x18000000
#define S3C2440_CS4_PHYS		0x20000000
#define S3C2440_CS5_PHYS		0x28000000
#define S3C2440_CS6_PHYS		0x30000000
#define S3C2440_CS7_PHYS		0x38000000


//	INTERRUPT

#define	SRCPND					__REG(0x4A000000)	//Interrupt request status
#define	INTMOD   				__REG(0x4A000004)	//Interrupt mode control
#define	INTMSK   				__REG(0x4A000008)	//Interrupt mask control
#define	PRIORITY 				__REG(0x4A00000C)	//IRQ priority control
#define	INTPND   				__REG(0x4A000010)	//Interrupt request status
#define	INTOFFSET				__REG(0x4A000014)	//Interrupt request source offset
#define	SUBSRCPND				__REG(0x4A000018)	//Sub source pending
#define	INTSUBMSK				__REG(0x4A00001C)	//Interrupt sub mask

#define ADC        				( 1 << 31 )
#define RTC        				( 1 << 30 )
#define SPI1       				( 1 << 29 )
#define UART0      				( 1 << 28 )
#define IIC        				( 1 << 27 )
#define USBH       				( 1 << 26 )
#define USBD       				( 1 << 25 )
#define NFCON	  				( 1 << 24 )
#define UART1      				( 1 << 23 )
#define SPI0       				( 1 << 22 )
#define SDI        				( 1 << 21 )
#define DMA3       				( 1 << 20 )
#define DMA2       				( 1 << 19 )
#define DMA1       				( 1 << 18 )
#define DMA0       				( 1 << 17 )
#define LCD        				( 1 << 16 )
#define UART2      				( 1 << 15 )
#define TIMER4     				( 1 << 14 )
#define TIMER3     				( 1 << 13 )
#define TIMER2     				( 1 << 12 )
#define TIMER1     				( 1 << 11 )
#define TIMER0     				( 1 << 10 )
#define WDT_AC97   				( 1 <<  9 )
#define TICK       				( 1 <<  8 )
#define BAT_FLT    				( 1 <<  7 )
#define CAM		   				( 1 <<  6 )
#define EINT8_23   				( 1 <<  5 )
#define EINT4_7    				( 1 <<  4 )
#define EINT3      				( 1 <<  3 )
#define EINT2      				( 1 <<  2 )
#define EINT1      				( 1 <<  1 )
#define EINT0					( 1 <<  0 )

#define SUB_AC97   				( 1 << 14 )
#define SUB_WDT   				( 1 << 13 )
#define SUB_CAM_P  				( 1 << 12 )
#define SUB_CAM_C  				( 1 << 11 )
#define SUB_ADC    				( 1 << 10 )
#define SUB_TC     				( 1 <<  9 )
#define SUB_ERR2   				( 1 <<  8 )
#define SUB_TXD2   				( 1 <<  7 )
#define SUB_RXD2   				( 1 <<  6 )
#define SUB_ERR1   				( 1 <<  5 )
#define SUB_TXD1   				( 1 <<  4 )
#define SUB_RXD1   				( 1 <<  3 )
#define SUB_ERR0   				( 1 <<  2 )
#define SUB_TXD0   				( 1 <<  1 )
#define SUB_RXD0   				( 1 <<  0 )

#define ALLMSK     				( 0xFFFFFFFF )
#define SUB_ALLMSK				( 0x7FFF )


//	PWM TIMER

#define TCFG0					__REG(0x51000000)	// Timer 0 configuration
#define TCFG1					__REG(0x51000004)	// Timer 1 configuration
#define TCON					__REG(0x51000008)	// Timer control
#define TCNTB0					__REG(0x5100000C)	// Timer count buffer 0
#define TCMPB0					__REG(0x51000010)	// Timer compare buffer 0
#define TCNTO0					__REG(0x51000014)	// Timer count observation 0
#define TCNTB1					__REG(0x51000018)	// Timer count buffer 1
#define TCMPB1					__REG(0x5100001C)	// Timer compare buffer 1
#define TCNTO1					__REG(0x51000020)	// Timer count observation 1

#define TCNTB2					__REG(0x51000024)	// Timer count buffer 2
#define TCMPB2					__REG(0x51000028)	// Timer compare buffer 2
#define TCNTO2					__REG(0x5100002C)	// Timer count observation 2

#define TCNTB3					__REG(0x51000030)	// Timer count buffer 3
#define TCMPB3					__REG(0x51000034)	// Timer compare buffer 3
#define TCNTO3					__REG(0x51000038)	// Timer count observation 3
#define TCNTB4					__REG(0x5100003C)	// Timer count buffer 4
#define TCNTO4					__REG(0x51000040)	// Timer count observation 4

// 타이머의 프리스케일러는 MAX, 데드존은 사용하지 않는다.
#define TCFG0_DEAD_ZONE_LEN		( 0x00 << 16 )
#define TCFG0_PRESCALER1		( 0xFF <<  8 )	// Timer 2,3 and 4
#define TCFG0_PRESCALER0		( 0xFF <<  0 )	// Timer 0 and 1

#define TCFG0_VALUE				( TCFG0_PRESCALER0 | TCFG0_PRESCALER1 | TCFG0_DEAD_ZONE_LEN )


// 타이머의 클럭은 PCLK 의 1/16 을 선택한다.
// MAX 프리스케일러는 선택하였으므로 81.91880us 의 resolution 을 갖는다.
// 최대 타이머 인터벌(16비트타이머 65535)은 5.3686sec 이다.
#define TCFG1_DMA				( 0 << 20 )		// 0=No select(All Interrup) 1=Timer0	2=Timer1	3=Timer2	4=Timer3	5=Timer4
#define TCFG1_MUX4				( 3 << 16 )		// 0=1/2	1=1/4	2=1/8	3=1/16	4=External TCLK1
#define TCFG1_MUX3				( 3 << 12 )		// 0=1/2	1=1/4	2=1/8	3=1/16	4=External TCLK1
#define TCFG1_MUX2				( 3 <<  8 )		// 0=1/2	1=1/4	2=1/8	3=1/16	4=External TCLK1
#define TCFG1_MUX1				( 3 <<  4 )		// 0=1/2	1=1/4	2=1/8	3=1/16	4=External TCLK0
#define TCFG1_MUX0				( 3 <<  0 )		// 0=1/2	1=1/4	2=1/8	3=1/16	4=External TCLK0
                            	
#define TCFG1_VALUE				( TCFG1_DMA | TCFG1_MUX4 | TCFG1_MUX3 | TCFG1_MUX2 | TCFG1_MUX1 | TCFG1_MUX0 )                                  


// Timer Control (TCON) Register
#define	TCON_TM4_ONE_SHOT		( 0 << 22 )
#define	TCON_TM4_AUTO_RELOAD	( 1 << 22 )
#define	TCON_TM4_UPDATE_NONE	( 0 << 21 )
#define	TCON_TM4_UPDATE_MANUAL	( 1 << 21 )
#define	TCON_TM4_STOP			( 0 << 20 )
#define	TCON_TM4_START			( 1 << 20 )

#define	TCON_TM3_ONE_SHOT		( 0 << 19 )
#define	TCON_TM3_AUTO_RELOAD	( 1 << 19 )
#define	TCON_TM3_INV_OFF		( 0 << 18 )
#define	TCON_TM3_INV_ON			( 1 << 18 )
#define	TCON_TM3_UPDATE_NONE	( 0 << 17 )
#define	TCON_TM3_UPDATE_MANUAL	( 1 << 17 )
#define	TCON_TM3_STOP			( 0 << 16 )
#define	TCON_TM3_START			( 1 << 16 )

#define	TCON_TM2_ONE_SHOT		( 0 << 15 )
#define	TCON_TM2_AUTO_RELOAD	( 1 << 15 )
#define	TCON_TM2_INV_OFF			( 0 << 14 )
#define	TCON_TM2_INV_ON			( 1 << 14 )
#define	TCON_TM2_UPDATE_NONE	( 0 << 13 )
#define	TCON_TM2_UPDATE_MANUAL	( 1 << 13 )
#define	TCON_TM2_STOP			( 0 << 12 )
#define	TCON_TM2_START			( 1 << 12 )
                                  
#define	TCON_TM1_ONE_SHOT		( 0 << 11 )
#define	TCON_TM1_AUTO_RELOAD	( 1 << 11 )
#define	TCON_TM1_INV_OFF		( 0 << 10 )
#define	TCON_TM1_INV_ON			( 1 << 10 )
#define	TCON_TM1_UPDATE_NONE	( 0 <<  9 )
#define	TCON_TM1_UPDATE_MANUAL	( 1 <<  9 )
#define	TCON_TM1_STOP			( 0 <<  8 )
#define	TCON_TM1_START			( 1 <<  8 )
                                           
#define	TCON_TM0_DZ_DISABLE		( 0 <<  4 )
#define	TCON_TM0_DZ_ENABLE		( 1 <<  4 )
#define	TCON_TM0_ONE_SHOT		( 0 <<  3 )
#define	TCON_TM0_AUTO_RELOAD	( 1 <<  3 )
#define	TCON_TM0_INV_OFF		( 0 <<  2 )
#define	TCON_TM0_INV_ON			( 1 <<  2 )
#define	TCON_TM0_UPDATE_NONE	( 0 <<  1 )
#define	TCON_TM0_UPDATE_MANUAL	( 1 <<  1 )
#define	TCON_TM0_STOP			( 0 <<  0 )
#define	TCON_TM0_START			( 1 <<  0 )


//	WATCH DOG TIMER

#define	WTCON					__REG(0x53000000)	// Watch-dog timer mode
#define WTDAT					__REG(0x53000004)	//Watch-dog timer data
#define WTCNT					__REG(0x53000008)	//Eatch-dog timer count

#define WTCON_PRESCALER			( 0xFF << 8 )
#define WTCON_WD_TIMER_ENABLE	( 0x01 << 5 )
#define	WTCON_CLOCK_SEL_16		( 0x00 << 3 )
#define	WTCON_CLOCK_SEL_32		( 0x01 << 3 ) 
#define	WTCON_CLOCK_SEL_64		( 0x02 << 3 )
#define	WTCON_CLOCK_SEL_128		( 0x03 << 3 )
#define WTCON_INT_ENABLE		( 0x01 << 2 )
#define WTCON_RESET_ENABLE		( 0x01 << 0 )

// Watch dog timer setup
// 프리스케일러는 255 이므로 선택하였으므로  PCLK 의 255 분주를 한다.
// 디바이더는 16을 선택하였으므로 최대 타이머 인터벌(16비트타이머 65535)은 5.3686sec 이다.
// t_watchdog = 50000000(PCLK) / (255+1) / 16 = TICKS_PER_SECOND
#define WTCON_VALUE				( WTCON_RESET_ENABLE | WTCON_CLOCK_SEL_16 | WTCON_PRESCALER )



//	NAND flash

#define NFCONF					__REG  (0x4E000000)      //NAND Flash configuration
#define NFCONT					__REG  (0x4E000004)      //NAND Flash configuration
#define NFCMD					__REG_B(0x4E000008)      //NADD Flash command
#define NFADDR					__REG_B(0x4E00000C)      //NAND Flash address
#define NFDATA					__REG_B(0x4E000010)      //NAND Flash data
#define NFMEMCCD1				__REG  (0x4E000014)      //NAND ECC1, ECC2
#define NFMEMCCD0				__REG  (0x4E000018)      //NAND ECC3, ECC4
#define NFMEMCCD				__REG  (0x4E00001C)      //NAND ECC
#define NFSTAT					__REG_B(0x4E000020)      //NAND Flash operation status
#define NFSTAT0					__REG  (0x4E000024)      //NAND Flash ECC [7:0] status
#define NFSTAT1					__REG  (0x4E000028)      //NAND Flash ECC [15:8] status
#define NFECC0					__REG  (0x4E00002C)      //NAND Flash ECC [7:0] 
#define NFECC1					__REG  (0x4E000030)      //NAND Flash ECC [15:8]
#define NFECC					__REG  (0x4E000034)      //NAND Flash ECC
#define NFSBLK					__REG  (0x4E000038)
#define NFEBLK					__REG  (0x4E00003C)



//	S3C2440 UART control registers

//	UART0 
#define UART0_BASE				((volatile Word  *)0x50000000)	// UART0 Base Address
#define UART0_ULCON				__REG(0x50000000)	// UART0 Line Control Register
#define UART0_UCON				__REG(0x50000004)	// UART0 Control Register
#define UART0_UFCON				__REG(0x50000008)	// UART0 FIFO Control Register
#define UART0_UMCON				__REG(0x5000000C)	// UART0 MODEM Control Register
#define UART0_UTRSTAT			__REG(0x50000010)	// UART0 TX/RX Status Register
#define UART0_UERSTAT			__REG(0x50000014)	// UART0 ERROR Status Register
#define UART0_UFSTAT			__REG(0x50000018)	// UART0 FIFO Status Register
#define UART0_UMSTAT			__REG(0x5000001C)	// UART0 MODEM Status Register
                            	
#ifdef __BIG_ENDIAN         	
#define UART0_UTXH				__REG(0x50000023)	// UART0 Transmit Buffer Register
#define UART0_URXH				__REG(0x50000027)	// UART0 Receive Buffer Register
#else //Little Endian       	
#define UART0_UTXH				__REG(0x50000020)	// UART0 Transmit Buffer Register
#define UART0_URXH				__REG(0x50000024)	// UART0 Receive Buffer Register
#endif                      	
                            	
//	UART1                   	
#define UART1_BASE				((volatile Word  *)0x50004000)	// UART1 Base Address
#define UART1_ULCON				__REG(0x50004000)	// UART1 Line Control Register
#define UART1_UCON				__REG(0x50004004)	// UART1 Control Register
#define UART1_UFCON				__REG(0x50004008)	// UART1 FIFO Control Register
#define UART1_UMCON				__REG(0x5000400C)	// UART1 MODEM Control Register
#define UART1_UTRSTAT			__REG(0x50004010)	// UART1 TX/RX Status Register
#define UART1_UERSTAT			__REG(0x50004014)	// UART1 ERROR Status Register
#define UART1_UFSTAT			__REG(0x50004018)	// UART1 FIFO Status Register
#define UART1_UMSTAT			__REG(0x5000401C)	// UART1 MODEM Status Register
                            	
#ifdef __BIG_ENDIAN         	
#define UART1_UTXH				__REG(0x50004023)	// UART1 Transmit Buffer Register
#define UART1_URXH				__REG(0x50004027)	// UART1 Receive Buffer Register
#else //Little Endian       	
#define UART1_UTXH				__REG(0x50004020)	// UART1 Transmit Buffer Register
#define UART1_URXH				__REG(0x50004024)	// UART1 Receive Buffer Register
#endif                      	
                            	
//	UART2                   	
#define UART2_BASE				((volatile Word  *)0x50008000)	// UART2 Base Address
#define UART2_ULCON				__REG(0x50008000)	// UART2 Line Control Register
#define UART2_UCON				__REG(0x50008004)	// UART2 Control Register
#define UART2_UFCON				__REG(0x50008008)	// UART2 FIFO Control Register
#define UART2_UMCON				__REG(0x5000800C)	// Reserved ( UART2 MODEM Control Register )
#define UART2_UTRSTAT			__REG(0x50008010)	// UART2 TX/RX Status Register
#define UART2_UERSTAT			__REG(0x50008014)	// UART2 ERROR Status Register
#define UART2_UFSTAT			__REG(0x50008018)	// UART2 FIFO Status Register
#define UART2_UMSTAT			__REG(0x5000801C)	// UART2 MODEM Status Register
                            	
#ifdef __BIG_ENDIAN         	
#define UART2_UTXH				__REG(0x50008023)	// UART2 Transmit Buffer Register
#define UART2_URXH				__REG(0x50008027)	// UART2 Receive Buffer Register
#else //Little Endian       	
#define UART2_UTXH				__REG(0x50008020)	// UART2 Transmit Buffer Register
#define UART2_URXH				__REG(0x50008024)	// UART2 Receive Buffer Register
#endif


//	UART Line Control Register 	[ Default : Normal mode, No parity, 1-stop bit, 8-bits ]

#define	ULCON_INFRA_RED_MODE	( 0x00 << 6 )   // 0 = Normal Mode 1 = Infra-Red Tx/Rx Mode
#define	ULCON_PARITY_NONE		( 0x00 << 3 )	// 0xx = No Parity	
#define	ULCON_PARITY_ODD		( 0x04 << 3 )	// 100 = Odd Parity	
#define	ULCON_PARITY_EVEN		( 0x05 << 3 )	// 101 = Even Parity
#define	ULCON_PARITY_FORCE1		( 0x06 << 3 )	// 110 = Parity forced/checked as 1	
#define	ULCON_PARITY_FORCE0		( 0x07 << 3 )	// 111 = Parity forced/checked as 0
#define	ULCON_STOP_BIT_1		( 0x00 << 2 )	// 0 = One Stop bit pre frame	
#define	ULCON_STOP_BIT_2		( 0x01 << 2 )	// 1 = Two Stop bit pre frame
#define	ULCON_DATA_BIT_5		( 0x00 >> 0 )	// 00=5-bits
#define	ULCON_DATA_BIT_6		( 0x01 >> 0 )	// 01=6-bits	
#define	ULCON_DATA_BIT_7		( 0x02 >> 0 )	// 10=7-bits	
#define	ULCON_DATA_BIT_8		( 0x03 >> 0 )	// 11=8-bits

#define	ULCON_VALUE				( ULCON_INFRA_RED_MODE | ULCON_PARITY_NONE | ULCON_STOP_BIT_1 | ULCON_DATA_BIT_8 )


//	UART Control Register

#define	UCON_FCLK_DIV			( 0x0 << 12 )	//  
#define	UCON_CLK_SELECT			( 0x0 << 10 )	//  0 = PCLK	1 = UCLK   3 = FCLK
#define	UCON_TX_INT_TYPE		( 0x1 <<  9 )	//  0 = Pulse 	1 = Level
#define	UCON_RX_INT_TYPE		( 0x0 <<  8 )	//  0 = Pulse 	1 = Level
#define	UCON_RX_TIME_OUT_EN		( 0x0 <<  7 )	//  0 = Disable	1 = Enable
#define	UCON_RX_ERR_STAT_INT_EN	( 0x1 <<  6 )	
#define	UCON_LOOPBACK_MODE		( 0x0 <<  5 )	//  0 = Normal Operation	1 = Loopback mode
#define	UCON_SEND_BRK_SGN		( 0x0 <<  4 )	//  0 = Normal Transmit		1 = Send Break Signal
#define	UCON_TX_MODE			( 0x1 <<  2 )	// 00 = Disable		01 = Interrupt Request or Polling Mode
#define	UCON_RX_MODE			( 0x1 <<  0 )	// 10 = DMA0 Request (Only for UART0)	11 = DMA1 Request (Only for UART1)
												//		DMA3 Request (Only for UART2)			
												
#define	UCON_VALUE				( UCON_CLK_SELECT     | UCON_TX_INT_TYPE	| UCON_RX_INT_TYPE		\
								| UCON_RX_TIME_OUT_EN | UCON_RX_ERR_STAT_INT_EN | UCON_LOOPBACK_MODE	\
								| UCON_SEND_BRK_SGN   | UCON_TX_MODE            | UCON_RX_MODE )


//	UART FIFO Control Register

#define	UFCON_TX_FIFO_TRG_LEVEL	( 0x0 << 6 )	// 00 = Empty   01 = 4-byte  10 =  8-byte  11 = 12-byte
#define	UFCON_RX_FIFO_TRG_LEVEL	( 0x0 << 4 )	// 00 = 4-byte  01 = 8-byte  10 = 12-byte  11 = 16-byte
#define	UFCON_TX_FIFO_RESET		( 0x1 << 2 )	// 0  = Normal	1  = Tx FIFO reset 
#define	UFCON_RX_FIFO_RESET		( 0x1 << 1 )	// 0  = Normal	1  = Rx FIFO reset 
#define	UFCON_FIFO_EN			( 0x1 << 0 )	// 0  = Disable	1  = Enable


//	UART MODEM Status Register

#define	UMCON_AFC				( 0x0 << 4 )	// 0 = Disable		1 = Emable
#define	UMCON_RTS				( 0x0 << 0 )	// 0 = 'H' Level	1 = 'L' Level


//	UART TX/RX Status Register

#define	UTRxSTAT_TX_EMPTY		( 0x1 << 2 )	// 0 = Not Empty	1 = Transmitter Empty
#define	UTRxSTAT_TX_BUFF_EMPTY	( 0x1 << 1 )	// 0 = The buffer register is not Empty		1 = Empty
#define	UTRxSTAT_RX_BUFF_REAYD	( 0x1 << 0 )	// 0 = Empty		1 = The buffer rebister has a received data



//	LCD Controller Register

#define LCD_LCDCON1				__REG(0x4D000000)
#define LCD_LCDCON2				__REG(0x4D000004)
#define LCD_LCDCON3				__REG(0x4D000008)
#define LCD_LCDCON4				__REG(0x4D00000C)
#define LCD_LCDCON5				__REG(0x4D000010)

// LCD Controller 1 Register
#define LCDCON1_CLKVAL(x)		((x) << 8)
#define LCDCON1_MMODE			(1<<7)
#define LCDCON1_DSCAN4			(0<<5)
#define LCDCON1_STN4			(1<<5)
#define LCDCON1_STN8			(2<<5)
#define LCDCON1_TFT				(3<<5)
#define LCDCON1_STN1BPP			(0<<1)
#define LCDCON1_STN2GREY		(1<<1)
#define LCDCON1_STN4GREY		(2<<1)
#define LCDCON1_STN8BPP			(3<<1)
#define LCDCON1_STN12BPP		(4<<1)
#define LCDCON1_TFT1BPP			(8<<1)
#define LCDCON1_TFT2BPP			(9<<1)
#define LCDCON1_TFT4BPP			(10<<1)
#define LCDCON1_TFT8BPP			(11<<1)
#define LCDCON1_TFT16BPP		(12<<1)
#define LCDCON1_TFT24BPP		(13<<1)
#define LCDCON1_ENVID			(1 <<0)

#define LCDCON1_MODEMASK		0x1E

// LCD Controller 2 Register
#define LCDCON2_VBPD(x)			( (x) << 24)
#define LCDCON2_LINEVAL(x)		( (x) << 14)
#define LCDCON2_VFPD(x)			( (x) <<  6)
#define LCDCON2_VSPW(x)			( (x) <<  0)
#define LCDCON2_GET_VBPD(x)		(((x) >> 24) & 0xFF)
#define LCDCON2_GET_VFPD(x)		(((x) >>  6) & 0xFF)
#define LCDCON2_GET_VSPW(x)		(((x) >>  0) & 0x3F)

// LCD Controller 3 Register
#define LCDCON3_HBPD(x)			( (x) << 19)
#define LCDCON3_WDLY(x)			( (x) << 19)
#define LCDCON3_HOZVAL(x)		( (x) <<  8)
#define LCDCON3_HFPD(x)			( (x) <<  0)
#define LCDCON3_LINEBLANK(x)	( (x) <<  0)
#define LCDCON3_GET_HBPD(x)		(((x) >> 19) & 0x7F)
#define LCDCON3_GET_HFPD(x)		(((x) >>  0) & 0xFF)

// LCD Controller 4 Register
#define LCDCON4_MVAL(x)			((x) << 8)
#define LCDCON4_HSPW(x)			((x) << 0)
#define LCDCON4_WLH(x)			((x) << 0)
#define LCDCON4_GET_HSPW(x)		( ((x) >>  0) & 0xFF)

// LCD Controller 5 Register
#define LCDCON5_BPP24BL			(1<<12)
#define LCDCON5_FRM565			(1<<11)
#define LCDCON5_INVVCLK			(1<<10)
#define LCDCON5_INVVLINE		(1<<9)
#define LCDCON5_INVVFRAME		(1<<8)
#define LCDCON5_INVVD			(1<<7)
#define LCDCON5_INVVDEN			(1<<6)
#define LCDCON5_INVPWREN		(1<<5)
#define LCDCON5_INVLEND			(1<<4)
#define LCDCON5_PWREN			(1<<3)
#define LCDCON5_ENLEND			(1<<2)
#define LCDCON5_BSWP			(1<<1)
#define LCDCON5_HWSWP			(1<<0)

/* Framebuffer Start Addressed */
#define LCD_LCDSADDR1			__REG(0x4D000014)
#define LCD_LCDSADDR2			__REG(0x4D000018)
#define LCD_LCDSADDR3			__REG(0x4D00001C)

#define LCDBANK(x)				((x) << 21)
#define LCDBASEU(x)				 (x)
#define OFFSIZE(x)				((x) << 11)
#define PAGEWIDTH(x)			 (x)

/* colour lookup and miscellaneous controls */
#define LCD_REDLUT				__REG(0x4D000020)
#define LCD_GREENLUT			__REG(0x4D000024)
#define LCD_BLUELUT				__REG(0x4D000028)

#define LCD_DITHMODE			__REG(0x4D00004C)
#define LCD_TPAL				__REG(0x4D000050)

#define TPAL_EN					(1<<24)

/* interrupt info */
#define LCD_LCDINTPND			__REG(0x4D000054)
#define LCD_LCDSRCPND			__REG(0x4D000058)
#define LCD_LCDINTMSK			__REG(0x4D00005C)
#define LCDINT_FIWSEL			(1<<2)
#define	LCDINT_FRSYNC			(1<<1)
#define LCDINT_FICNT			(1<<0)

#define LCD_LPCSEL				__REG(0x4D000060)



// GPIO

#define GPACON					__REG(0x56000000) //Port A control
#define GPADAT					__REG(0x56000004) //Port A data
                    				
#define GPBCON					__REG(0x56000010) //Port B control
#define GPBDAT					__REG(0x56000014) //Port B data
#define GPBUP					__REG(0x56000018) //Pull-up control B
                    				
#define GPCCON					__REG(0x56000020) //Port C control
#define GPCDAT					__REG(0x56000024) //Port C data
#define GPCUP					__REG(0x56000028) //Pull-up control C
                    				
#define GPDCON					__REG(0x56000030) //Port D control
#define GPDDAT					__REG(0x56000034) //Port D data
#define GPDUP					__REG(0x56000038) //Pull-up control D
                    				
#define GPECON					__REG(0x56000040) //Port E control
#define GPEDAT					__REG(0x56000044) //Port E data
#define GPEUP					__REG(0x56000048) //Pull-up control E
                    				
#define GPFCON					__REG(0x56000050) //Port F control
#define GPFDAT					__REG(0x56000054) //Port F data
#define GPFUP					__REG(0x56000058) //Pull-up control F
                    				
#define GPGCON					__REG(0x56000060) //Port G control
#define GPGDAT					__REG(0x56000064) //Port G data
#define GPGUP					__REG(0x56000068) //Pull-up control G
                    				
#define GPHCON					__REG(0x56000070) //Port H control
#define GPHDAT					__REG(0x56000074) //Port H data
#define GPHUP					__REG(0x56000078) //Pull-up control H
                            	
#define GPJCON					__REG(0x560000D0) //Port H control
#define GPJDAT					__REG(0x560000D4) //Port H data
#define GPJUP					__REG(0x560000D8) //Pull-up control H
                    				
                            	
                    				
#define MISCCR					__REG(0x56000080) //Miscellaneous control
#define DCLKCON					__REG(0x56000084) //DCLK0/1 control
#define EXTINT0					__REG(0x56000088) //External interrupt control register 0
#define EXTINT1					__REG(0x5600008c) //External interrupt control register 1
#define EXTINT2					__REG(0x56000090) //External interrupt control register 2
#define EINTFLT0				__REG(0x56000094) //Reserved
#define EINTFLT1				__REG(0x56000098) //Reserved
#define EINTFLT2				__REG(0x5600009c) //External interrupt filter control register 2
#define EINTFLT3				__REG(0x560000a0) //External interrupt filter control register 3
#define EINTMASK				__REG(0x560000a4) //External interrupt mask
#define EINTPEND				__REG(0x560000a8) //External interrupt pending
#define GSTATUS0				__REG(0x560000ac) //External pin status
#define GSTATUS1				__REG(0x560000b0) //Chip ID(0x32440000)
#define GSTATUS2				__REG(0x560000b4) //Reset type
#define GSTATUS3				__REG(0x560000b8) //Saved data0(32-bit) before entering POWER_OFF mode 
#define GSTATUS4				__REG(0x560000bc) //Saved data0(32-bit) before entering POWER_OFF mode 
                            	
#define DSC0					__REG(0x560000c4) // Control the Memory I/O drive strength
#define DSC1					__REG(0x560000c8) // Control the Memory I/O drive strength
                            	
#define MSLCON					__REG(0x560000cc) // Select memory interface status when in SLEEP mode
                            	

//	GENERAL STATUS Register (GSTATUS0)

#define GSTATUS0_NWAIT			( 0x08 << 3 )
#define GSTATUS0_NCON			( 0x04 << 2 )
#define GSTATUS0_RNB			( 0x02 << 1 )
#define GSTATUS0_BATT_FLT		( 0x01 << 0 )

#define GPIO_bit(x)				( 1 << ((x) & 0xf))

#endif  //__S3C2440_H__

