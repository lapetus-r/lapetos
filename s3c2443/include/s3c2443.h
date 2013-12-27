/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃			  														  lapetOS			   													   ┃
┃				 						 [ General Purpose Kernel for Embedded System ]									   ┃
┃			  																   																	   ┃
┃			  							  					SangMyung University									   					   ┃
┃			  							  				  Computer Science Major												       ┃
┃			  																				   													   ┃
┃					  					  Made By: Yoo Sang-Gi / Park Il-Kwon, 2011-2012							  	   ┃
┃			  											 	 File Name: s3c2443.h 													   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

#ifndef __S3C2443_CONFIG__
#define __S3C2443_CONFIG__

#define NONCACHE_STARTADDRESS		0x31000000
/* REGISTER READ & WRITE FUCTION */

#define readl(addr)				(*(volatile unsigned long *)(addr))	
#define readw(addr)			(*(volatile unsigned short *)(addr))
#define readb(addr)			(*(volatile unsigned char *)(addr))
#define writel(val, addr)		(*(volatile unsigned long *)(addr) = val)
#define writew(val, addr)		(*(volatile unsigned short *)(addr) = val)
#define writeb(val, addr)		(*(volatile unsigned char *)(addr) = val)

/* CLOCK */
#define	FCLK					534000000
#define	HCLK					FCLK/3		// FCLK=534000000	HCLK=178000000
#define	PCLK					FCLK/8		// FCLK=534000000	PCLK= 66750000


/* UART */
#define UTRSTAT1					(*(volatile unsigned *)0x50004010)		//UART 1 Tx/Rx status
#define UTXH1						(*(volatile unsigned char *)0x50004020)		//UART 1 Tx/Rx status
#define URXH1						(*(volatile unsigned char *)0x50004024)		//UART 1 Receive buffer

#define UART2_BASE				(*(volatile unsigned char *)0x50008000)
#define	UTRxSTAT_TX_EMPTY		( 0x1 << 2 )	// 0 = Not Empty	1 = Transmitter Empty
#define	UTRxSTAT_RX_BUFF_REAYD	( 0x1 << 0 )	// 0 = Empty		1 = The buffer rebister

/* UART */
#define UART1_BASE				(*(volatile unsigned *)0x50004000)	// UART1 Base Address
#define UART1_ULCON			(*(volatile unsigned char *)0x50004000)	// UART1 Line Control Register
#define UART1_UCON				(*(volatile unsigned char *)0x50004004)	// UART1 Control Register
#define UART1_UFCON			(*(volatile unsigned char *)0x50004008)	// UART1 FIFO Control Register
#define UART1_UMCON			(*(volatile unsigned char *)0x5000400C)	// UART1 MODEM Control Register
#define UART1_UTRSTAT			(*(volatile unsigned char *)0x50004010)	// UART1 TX/RX Status Register
#define UART1_UERSTAT			(*(volatile unsigned char *)0x50004014)	// UART1 ERROR Status Register
#define UART1_UFSTAT			(*(volatile unsigned char *)0x50004018)	// UART1 FIFO Status Register
#define UART1_UMSTAT			(*(volatile unsigned char *)0x5000401C)	// UART1 MODEM Status Register
                            	
#ifdef __BIG_ENDIAN         	
#define UART1_UTXH				(*(volatile unsigned char *)0x50004023)	// UART1 Transmit Buffer Register
#define UART1_URXH				(*(volatile unsigned char *)0x50004027)	// UART1 Receive Buffer Register
#else //Little Endian       	
#define UART1_UTXH				(*(volatile unsigned char *)0x50004020)	// UART1 Transmit Buffer Register
#define UART1_URXH				(*(volatile unsigned char *)0x50004024)	// UART1 Receive Buffer Register
#endif                      	
                            	
/* KEY */
#define GPFCON		(*(volatile unsigned *)0x56000050)		//Configure the pins of port F
#define GPFDAT			(*(volatile unsigned *)0x56000054)		//The data for port F

/* LCD */
#define LCD_FRAME_BUFFER		NONCACHE_STARTADDRESS

#define LCD_WIN0_FRAME_BUFFER0		(LCD_FRAME_BUFFER)
#define LCD_WIN0_FRAME_BUFFER1		(LCD_FRAME_BUFFER+0x100000)
#define LCD_WIN1_FRAME_BUFFER		(LCD_FRAME_BUFFER+0x200000)

#define GPGCON		(*(volatile unsigned *)0x56000060)		//Configure the pins of port G
#define GPGDAT			(*(volatile unsigned *)0x56000064)		//The data for port G
#define GPBCON		(*(volatile unsigned *)0x56000010)		//Configure the pins of port B
#define GPBDAT			(*(volatile unsigned *)0x56000014)		//The data for port B

#define MISCCR			(*(volatile unsigned *)0x56000080)		//Miscellaneous Control register
#define MC_LCD_SEL				( 1 << 28)									//TFT Controller LCD output port

#define GPCCON		(*(volatile unsigned *)0x56000020)		//Configure the pins of port C
#define GPDCON		(*(volatile unsigned *)0x56000030)		//Configure the pins of port D
/* TFT-LCD */
#define VIDCON0		(*(volatile unsigned *)0x4c800000)		//Video Control 0 register
#define VIDCON1		(*(volatile unsigned *)0x4c800004)		//Video Control 1 register
#define VIDTCON0		(*(volatile unsigned *)0x4c800008)		//Video Time Control 0 register
#define VIDTCON1		(*(volatile unsigned *)0x4c80000c)			//Video Time Control 1 register
#define VIDTCON2		(*(volatile unsigned *)0x4c800010)		//Video Time Control 2 register

#define WINCON0		(*(volatile unsigned *)0x4c800014)		//Window Control 0 register
#define VIDOSD0A		(*(volatile unsigned *)0x4c800028)		//Video Window 0's Position Control register
#define VIDOSD0B		(*(volatile unsigned *)0x4c80002c)			//Video Window 0's Position Control register
#define VIDW00ADD0B		(*(volatile unsigned *)0x4c800064)			//Window 0's Buffer Start address register, buffer 0
#define VIDW00ADD0B1	(*(volatile unsigned *)0x4c800068)
#define VIDW00ADD2B0	(*(volatile unsigned *)0x4c800094)
#define VIDW00ADD1B1	(*(volatile unsigned *)0x4c800080)
#define VIDW00ADD1B0	(*(volatile unsigned *)0x4c80007C)
#define VIDW00ADD2B1	(*(volatile unsigned *)0x4c800098)
#define WIN0MAP		(*(volatile unsigned *)0x4c8000D0)		//Window Color Control

#define VIDCON0_S_RGB_IF					( 0 << 22 )
#define VIDCON0_S_BGR_PAR					( 1 << 13 )
#define VIDCON0_CLKVAL_F_SHIFT			( 6)				//bit shift
#define VIDCON0_S_VCLK_GATING_OFF	( 1 << 5 )
#define VIDCON0_S_CLKDIR_DIVIDED		( 1 << 4 )
#define VIDCON0_S_CLKSEL_HCLK			( 0 << 2 )

/* VIDCON1 */
#define VIDCON1_S_VCLK_FALL_EDGE_FETCH		(0<<7)
//#define VIDCON1_S_VCLK_RISE_EDGE_FETCH		(1<<7)
#define VIDCON1_S_HSYNC_INVERTED			(1<<6)
#define VIDCON1_S_VSYNC_INVERTED			(1<<5)
//#define VIDCON1_S_VDEN_INVERTED				(1<<4)

/* VIDTCON0,1 */
#define VIDTCON0_BPD_S						(16)
#define VIDTCON0_FPD_S						(8)
#define VIDTCON0_SPW_S						(0)
/* VIDTCON2 */
#define VIDTCON2_LINEVAL_S					(11)
#define VIDTCON2_HOZVAL_S					(0)
#define WINCON_BUFSEL						(23)
#define WINCON_BUFAUTOEN					(22)
#define WINCON_SWAP_S						(16)
#define WINCON_BURSTLEN_S				(9)
#define WINCON_BLENDING_S				(6)
#define WINCON_BPP_S							(2)
#define WINCON_ALPHA_S						(1)

#define WINCONx_4WORD_BURST			(2)
#define WINCONx_24BPP_888				(11)
/* VIDOSDxA,B,C */
#define VIDOSDxAB_HORIZON_X_S			(11)
#define VIDOSDxAB_VERTICAL_Y_S			(0)
#define VIDOSDxC_ALPHA0_S					(12)

/* VIDWxADD2 */
#define VIDWxADD2_OFFSET_SIZE_S		(13)
#define VIDWxADD2_PAGE_WIDTH_S		(0)

#define LCD_XSIZE_TFT							(480)
#define LCD_YSIZE_TFT							(272)
#define LCD_PIXEL_SIZE						 	130560 // 480 X 272 = 130560
#define LCD_COLOR_RED    					0xFF0000
#define LCD_COLOR_GREEN  					0x00FF00
#define LCD_COLOR_BLUE   					0x0000FF

/* TIMER */
#define TCFG0			(*(volatile unsigned *)0x51000000)		//Configures the two 8-bit presclers
#define TCFG1			(*(volatile unsigned *)0x51000004)		//5-MUX & DMA mode selecton

#define TCFG1_DMA				( 0 << 20 )		// 0=No select(All Interrup) 1=Timer0	2=Timer1	3=Timer2	4=Timer3	5=Timer4
#define TCFG1_MUX4				( 3 << 16 )		// 0=1/2	1=1/4	2=1/8	3=1/16	4=External TCLK1
#define TCFG1_MUX3				( 3 << 12 )		// 0=1/2	1=1/4	2=1/8	3=1/16	4=External TCLK1
#define TCFG1_MUX2				( 3 <<  8 )		// 0=1/2	1=1/4	2=1/8	3=1/16	4=External TCLK1
#define TCFG1_MUX1				( 3 <<  4 )		// 0=1/2	1=1/4	2=1/8	3=1/16	4=External TCLK0
#define TCFG1_MUX0				( 3 <<  0 )		// 0=1/2	1=1/4	2=1/8	3=1/16	4=External TCLK0

#define TCON			(*(volatile unsigned *)0x51000008)		//Timer Control
#define TCNTB0			(*(volatile unsigned *)0x5100000c)		//Timer 0 Count Buffer
#define TCMPB0		(*(volatile unsigned *)0x51000010)		//Timer 0 Compare Buffer
#define TCNTO0			(*(volatile unsigned *)0x51000014)		//Timer 0 Count Observation
#define TCNTB1			(*(volatile unsigned *)0x51000018)		//Timer 1 Count Buffer
#define TCMPB1		(*(volatile unsigned *)0x5100001c)		//Timer 1 Compare Buffer
#define TCNTO1			(*(volatile unsigned *)0x51000020)		//Timer 1 Count Observation
#define TCNTB2			(*(volatile unsigned *)0x51000024)		//Timer 2 Count Buffer
#define TCMPB2		(*(volatile unsigned *)0x51000028)		//Timer 2 Compare Buffer
#define TCNTO2			(*(volatile unsigned *)0x5100002c)		//Timer 2 Count Observation
#define TCNTB3			(*(volatile unsigned *)0x51000030)		//Timer 3 Count Buffer
#define TCMPB3		(*(volatile unsigned *)0x51000034)		//Timer 3 Compare Buffer
#define TCNTO3			(*(volatile unsigned *)0x51000038)		//Timer 3 Count Observation
#define TCNTB4			(*(volatile unsigned *)0x5100003c)		//Timer 4 Count Buffer
#define TCNTO4			(*(volatile unsigned *)0x51000040)		//Timer 4 Count Observation

#define	TCON_TM0_STOP								( 0 <<  0 )
#define	TCON_TM0_START								( 1 <<  0 )   
#define	TCON_TM0_UPDATE_NONE					( 0 <<  1 )
#define	TCON_TM0_UPDATE_MANUAL				( 1 <<  1 )
#define	TCON_TM0_INV_OFF							( 0 <<  2 )
#define	TCON_TM0_INV_ON							( 1 <<  2 )
#define	TCON_TM0_ONE_SHOT						( 0 <<  3 )
#define	TCON_TM0_AUTO_RELOAD					( 1 <<  3 )
#define	TCON_TM0_DZ_DISABLE						( 0 <<  4 )
#define	TCON_TM0_DZ_ENABLE						( 1 <<  4 )
                              
#define	TCON_TM1_STOP								( 0 <<  8 )
#define	TCON_TM1_START								( 1 <<  8 )
#define	TCON_TM1_UPDATE_NONE					( 0 <<  9 )
#define	TCON_TM1_UPDATE_MANUAL				( 1 <<  9 )
#define	TCON_TM1_INV_OFF							( 0 << 10 )
#define	TCON_TM1_INV_ON							( 1 << 10 )
#define	TCON_TM1_ONE_SHOT						( 0 << 11 )
#define	TCON_TM1_AUTO_RELOAD					( 1 << 11 )

#define	TCON_TM2_STOP								( 0 << 12 )
#define	TCON_TM2_START								( 1 << 12 )
#define	TCON_TM2_UPDATE_NONE					( 0 << 13 )
#define	TCON_TM2_UPDATE_MANUAL				( 1 << 13 )
#define	TCON_TM2_INV_OFF							( 0 << 14 )
#define	TCON_TM2_INV_ON							( 1 << 14 )
#define	TCON_TM2_ONE_SHOT						( 0 << 15 )
#define	TCON_TM2_AUTO_RELOAD					( 1 << 15 )

#define	TCON_TM3_STOP								( 0 << 16 )
#define	TCON_TM3_START								( 1 << 16 )
#define	TCON_TM3_UPDATE_NONE					( 0 << 17 )
#define	TCON_TM3_UPDATE_MANUAL				( 1 << 17 )
#define	TCON_TM3_INV_OFF							( 0 << 18 )
#define	TCON_TM3_INV_ON							( 1 << 18 )
#define	TCON_TM3_ONE_SHOT						( 0 << 19 )
#define	TCON_TM3_AUTO_RELOAD					( 1 << 19 )

#define	TCON_TM4_STOP								( 0 << 20 )
#define	TCON_TM4_START								( 1 << 20 )
#define	TCON_TM4_UPDATE_NONE					( 0 << 21 )
#define	TCON_TM4_UPDATE_MANUAL				( 1 << 21 )
#define	TCON_TM4_ONE_SHOT						( 0 << 22 )
#define	TCON_TM4_AUTO_RELOAD					( 1 << 22 )

/* SYSTEM */
#define SWIRST			(*(volatile unsigned *)0x4C000044)		//Software Reset Control

/* INTERRUPT */
#define	INTMSK 		(*(volatile unsigned *)0x4A000008)
#define	INTMOD 		(*(volatile unsigned *)0x4A000004)
#define	SRCPND		(*(volatile unsigned *)0x4A000000)	//Interrupt request status
#define	INTPND   		(*(volatile unsigned *)0x4A000010)	//Interrupt request status

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

#endif

