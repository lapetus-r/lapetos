/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃			  														  lapetOS			   													   ┃
┃				 						 [ General Purpose Kernel for Embedded System ]									   ┃
┃			  																   																	   ┃
┃			  							  					SangMyung University									   					   ┃
┃			  							  				  Computer Science Major												       ┃
┃			  																				   													   ┃
┃					  					  Made By: Yoo Sang-Gi / Park Il-Kwon, 2011-2012							  	   ┃
┃			  											 	 File Name: TFTLCD.h	 													   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/#ifndef __LCD_H__
#define __LCD_H__



#define TFT_16BIT	0
#define TFT_24BIT	3

#define	SEMIHOSTING	FALSE

#define _NONCACHE_STARTADDRESS		0x31000000

//#define LCD_FRAME_BUFFER			(_NONCACHE_STARTADDRESS + 0x1000000)

#define LCD_WIN0_FRAME_BUFFER0		(LCD_FRAME_BUFFER)
#define LCD_WIN0_FRAME_BUFFER1		(LCD_FRAME_BUFFER+0x100000)
#define LCD_WIN1_FRAME_BUFFER		(LCD_FRAME_BUFFER+0x200000)

#define MTF430_VBPD		(2)
#define MTF430_VFPD		(2)
#define MTF430_VSPW		(10)
#define MTF430_HBPD		(2)
#define MTF430_HFPD		(2)
#define MTF430_HSPW		(41)
#define MTF430_XSIZE	(480)
#define MTF430_YSIZE	(272)
#define MTF430_FRAME_RATE	60

#define LCD_XSIZE	(MTF430_XSIZE)	// real screen
#define LCD_YSIZE	(MTF430_YSIZE)
#define SCR_XSIZE 	(LCD_XSIZE*1)   // virtual screen  
#define SCR_YSIZE	(LCD_YSIZE*1)

#define LCD_ON			GPGDAT |= (1<<4)
#define LCD_OFF			GPGDAT &= ~(1<<4)

//* VIDCON0	
//#define VIDCON0_S_RGB_IF					(0<<22)
#define VIDCON0_S_RGB_PAR					(0<<13)
//#define VIDCON0_S_BGR_PAR					(1<<13)
#define VIDCON0_S_CLKVAL_F_AlWAYS_UPDATE	(0<<12)
#define VIDCON0_S_CLKVAL_F_SOF_UPDATE		(1<<12)
#define VIDCON0_S_VCLK_GATING_ON			(0<<5)
//#define VIDCON0_S_VCLK_GATING_OFF			(1<<5)
#define VIDCON0_S_CLKDIR_DIRECT				(0<<4)
//#define VIDCON0_S_CLKDIR_DIVIDED			(1<<4)
//#define VIDCON0_S_CLKSEL_HCLK				(0<<2)
#define VIDCON0_S_CLKSEL_UPLL				(1<<2)
#define VIDCON0_S_ENVID_OFF					(0<<1)
#define VIDCON0_S_EVVID_ON					(1<<1)
#define VIDCON0_S_ENVID_F_OFF				(0<<0)
#define VIDCON0_S_ENVID_F_ON				(1<<0)
//bit shift
//#define VIDCON0_CLKVAL_F_SHIFT				(6)
#define VIDCON0_PNRMODE_SHIFT				(13)

//* VIDCON1
#define VIDCON1_S_VCLK_FALL_EDGE_FETCH		(0<<7)
#define VIDCON1_S_VCLK_RISE_EDGE_FETCH		(1<<7)
#define VIDCON1_S_HSYNC_INVERTED			(1<<6)
#define VIDCON1_S_VSYNC_INVERTED			(1<<5)
#define VIDCON1_S_VDEN_INVERTED				(1<<4)

//* VIDTCON0,1
//bit shift
#define VIDTCON0_BPD_S				(16)
#define VIDTCON0_FPD_S				(8)
#define VIDTCON0_SPW_S				(0)

//* VIDTCON2
//bit shift
#define VIDTCON2_LINEVAL_S			(11)
#define VIDTCON2_HOZVAL_S			(0)


//* WINCON1to4
#define WINCONx_BIT_SWAP_ON			(1<<18)	//shift on basis of half-word swap
#define WINCONx_BYTE_SWAP_ON		(1<<17)	//shift on basis of half-word swap
#define WINCONx_HALFW_SWAP_ON		(1<<16)	//shift on basis of half-word swap
//#define WINCONx_4WORD_BURST			(2<<9)
#define WINCONx_8WORD_BURST			(1<<9)
#define WINCONx_16WORD_BURST		(0<<9)
#define WINCONx_1BPP_PALLET			(0<<2)
#define WINCONx_2BPP_PALLET			(1<<2)
#define WINCONx_4BPP_PALLET			(2<<2)
#define WINCONx_8BPP_PALLET			(3<<2)
#define WINCONx_8BPP_NO_PALLET		(4<<2)
#define WINCONx_16BPP_565			(5<<2)
#define WINCONx_16BPP_A555			(6<<2)
#define WINCONx_16BPP_1555			(7<<2)
#define WINCONx_18BPP_666			(8<<2)
#define WINCONx_18BPP_A665			(9<<2)
#define WINCONx_19BPP_A666			(10<<2)
//#define WINCONx_24BPP_888			(11<<2)
#define WINCONx_24BPP_A887			(12<<2)
#define WINCONx_25BPP_A888			(13<<2)
#define WINCONx_ALPHA_MODE_0		(0<<1)
#define WINCONx_ALPHA_MODE_1		(1<<1)

//bit shift
#define WINCON_BUFSEL				(23)
#define WINCON_BUFAUTOEN			(22)
#define WINCON_SWAP_S				(16)
#define WINCON_BURSTLEN_S			(9)
#define WINCON_BLENDING_S			(6)
#define WINCON_BPP_S				(2)
#define WINCON_ALPHA_S				(1)

//* VIDWxADD2
//bit shift
#define VIDWxADD2_OFFSET_SIZE_S		(13)
#define VIDWxADD2_PAGE_WIDTH_S		(0)


//* VIDOSDxA,B,C
//bit shift
#define VIDOSDxAB_HORIZON_X_S		(11)
#define VIDOSDxAB_VERTICAL_Y_S		(0)
#define VIDOSDxC_ALPHA0_S			(12)


#define LCD_WIN_0					0
#define LCD_WIN_1					1
#define LCD_WIN_ALL					2

#define LCD_BUF_0					0
#define LCD_BUF_1					1

void TFTLCD_Init(unsigned int bit);
void TFT0_16BITPutPixel(unsigned int x,unsigned int y,int color);
void TFT1_16BITPutPixel(unsigned int x,unsigned int y,int color);
void TFT0_24BITPutPixel(unsigned int x,unsigned int y,int color);
void TFT1_24BITPutPixel(unsigned int x,unsigned int y,int color);

// TFTLCD_LIB.c
int lprintf(const char *fmt, ...);
int LCD_Write( char *str, int size );
void lputs(unsigned int x, unsigned int y, unsigned int color, char *str);
void bg_lputs(unsigned int x, unsigned int y, unsigned int color, unsigned int bgcolor, char *str);
void TFT_Box(int x1, int y1, int x2, int y2, int color);
void TFT_Box_Select_Color(int i, int color);
void LCD_Line(int x1, int y1, int x2, int y2, int color);
void TFT_SWITCH(unsigned int x);
void TFT_CLR(unsigned int k);
void TFT_Intro(void);
void LCD_SQUARE(void);
void LCD_TIMER_Select( int n);
int State(int create, int running);
void LCD_LOGO(void);

#endif
