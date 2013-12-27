/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃			  														  lapetOS			   													   ┃
┃				 						 [ General Purpose Kernel for Embedded System ]									   ┃
┃			  																   																	   ┃
┃			  							  					SangMyung University									   					   ┃
┃			  							  				  Computer Science Major												       ┃
┃			  																				   													   ┃
┃					  					  Made By: Yoo Sang-Gi / Park Il-Kwon, 2011-2012							  	   ┃
┃			  											 	 File Name: TFTLCD.c	 													   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

#include <include.h>

unsigned short  lcd_horizon_value = 0;
unsigned short  lcd_line_value = 0;

unsigned char lcd_vbpd = 0;
unsigned char lcd_vfpd = 0;
unsigned char lcd_vspw = 0;
unsigned char lcd_hbpd = 0;
unsigned char lcd_hfpd = 0;
unsigned char lcd_hspw = 0;

unsigned char lcd_frame_rate = 0;

static unsigned int tft_bit = TFT_24BIT;
static volatile unsigned int *lcd_framebuffer = 0;
static volatile unsigned int *lcd_framebuffer1 = 0;

// Current Frame Buffer
void (*Put_Pixel)(unsigned int x, unsigned int y, int color) = TFT0_24BITPutPixel;
// Background Frame Buffer
void (*Put_Pixel_back)(unsigned int x, unsigned int y, int color) = TFT1_24BITPutPixel;

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃				 												 [ TFTLCD_Init ]															   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/
void TFTLCD_Init(unsigned int bit)
{
	unsigned char clkval=0;
	unsigned int pagewidth_in_byte = 0;
	
	if((bit != TFT_24BIT) && (bit != TFT_16BIT)) return;
	tft_bit = bit;
	
	MISCCR |= (1<<28);		// TFT LCD Control En
	GPCCON = 0xaaaaaaaa;	// CTRL, VD[7:0]
	GPDCON = 0xaaaaaaaa;	// VD[23:8]
	
	
	// BackLight 부분 미구현..
	GPBCON = (GPBCON & ~(3<<6)) | (1<<6);	// Backlight PWM Control (GPB3)
	GPBCON = (GPBCON & ~(3<<6)) | (2<<6);	// Backlight PWM Control (TOUT3)
	GPBDAT |= (1<<3);
	
	GPGCON = (GPGCON & ~(3<<8)) | (1<<8); // LCD_PWRDN (GPG4)
	LCD_OFF;

	clkval = (unsigned char)(((float)HCLK/(float)((MTF430_VBPD + MTF430_VFPD + MTF430_VSPW + MTF430_YSIZE)*(MTF430_HBPD + MTF430_HFPD + MTF430_HSPW + MTF430_XSIZE)*MTF430_FRAME_RATE))) - 1;
	VIDCON0 = (VIDCON0_S_RGB_IF|VIDCON0_S_RGB_PAR|(clkval <<VIDCON0_CLKVAL_F_SHIFT)|VIDCON0_S_VCLK_GATING_OFF|VIDCON0_S_CLKDIR_DIVIDED|VIDCON0_S_CLKSEL_HCLK);
	VIDCON1 = VIDCON1_S_HSYNC_INVERTED|VIDCON1_S_VSYNC_INVERTED;

	// Timing	
	VIDTCON0=((MTF430_VBPD-1)<<VIDTCON0_BPD_S)|((MTF430_VFPD-1)<<VIDTCON0_FPD_S)|((MTF430_VSPW-1)<<VIDTCON0_SPW_S);
	VIDTCON1=((MTF430_HBPD-1)<<VIDTCON0_BPD_S)|((MTF430_HFPD-1)<<VIDTCON0_FPD_S)|((MTF430_HSPW-1)<<VIDTCON0_SPW_S);
	VIDTCON2 = ((MTF430_YSIZE-1)<<VIDTCON2_LINEVAL_S)|((MTF430_XSIZE-1)<<VIDTCON2_HOZVAL_S);
	
	switch(tft_bit) {
	case TFT_16BIT:
		pagewidth_in_byte = LCD_XSIZE / 8 * 16;
		WINCON0 = WINCONx_HALFW_SWAP_ON|WINCONx_4WORD_BURST|WINCONx_16BPP_565; //  inverse halfword, 4word burst, 16bpp,
		break;
	case TFT_24BIT:
	default:
		pagewidth_in_byte = LCD_XSIZE / 8 * 32;
		WINCON0 = WINCONx_16WORD_BURST|WINCONx_24BPP_888; // 16word burst, 24bpp, 
		break;
	}
	
	TFT_SWITCH(0);
	
	VIDOSD0A = (0<<VIDOSDxAB_HORIZON_X_S)|(0<<VIDOSDxAB_VERTICAL_Y_S); // OSD LEFT TOP PIXEL
	VIDOSD0B = ((MTF430_XSIZE-1)<<VIDOSDxAB_HORIZON_X_S)|((MTF430_YSIZE-1)<<VIDOSDxAB_VERTICAL_Y_S);//OSD RIGHT BOTTOM PIXEL 	

	lcd_framebuffer = (unsigned int *)LCD_WIN0_FRAME_BUFFER0;
	
	VIDW00ADD0B = (unsigned int)lcd_framebuffer;
	VIDW00ADD1B0 = (unsigned int)lcd_framebuffer + (pagewidth_in_byte)*(LCD_YSIZE);
	// buffer size 
	VIDW00ADD2B0 = (0<<13)|pagewidth_in_byte;

	lcd_framebuffer1 = (unsigned int *)LCD_WIN0_FRAME_BUFFER1;
	VIDW00ADD0B1 = (unsigned int)lcd_framebuffer1;
	VIDW00ADD1B1 = (unsigned int)lcd_framebuffer1 + (pagewidth_in_byte)*(LCD_YSIZE);
	// buffer size 
	VIDW00ADD2B1 = (0<<13)|pagewidth_in_byte;

	WIN0MAP = 0;
	VIDCON0 |= 0x03; // ENVID On using Per Frame method
  WINCON0 |= 0x01; //LCD ON

	LCD_ON;
}

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃														 [  TFT0_16BITPutPixel ]										   				   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/
void TFT0_16BITPutPixel(unsigned int x,unsigned int y,int color)
{
	if(x<LCD_XSIZE && y< LCD_YSIZE) {
		color = ((color & 0xf80000) >> 8) | ((color & 0xfc00) >> 5) | ((color & 0xf8) >> 3);
		*((unsigned short *)lcd_framebuffer + (x + y * LCD_XSIZE)) = color;
	}
}

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃														 [  TFT1_16BITPutPixel ]										   				   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/
void TFT1_16BITPutPixel(unsigned int x,unsigned int y,int color)
{
	if(x<LCD_XSIZE && y< LCD_YSIZE) {
		color = ((color & 0xf80000) >> 8) | ((color & 0xfc00) >> 5) | ((color & 0xf8) >> 3);
		*((unsigned short *)lcd_framebuffer1 + (x + y * LCD_XSIZE)) = color;
	}
}

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃														 [  TFT0_24BITPutPixel ]										   				   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/
void TFT0_24BITPutPixel(unsigned int x,unsigned int y,int color)
{
	if(x<LCD_XSIZE && y< LCD_YSIZE)
		*(lcd_framebuffer + x + (y * LCD_XSIZE)) = color;
}

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃														 [  TFT1_24BITPutPixel ]										   				   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/
void TFT1_24BITPutPixel(unsigned int x,unsigned int y,int color)
{
	if(x<LCD_XSIZE && y< LCD_YSIZE)
		*(lcd_framebuffer1 + x + (y * LCD_XSIZE)) = color;
}
/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃															 [  TFT_SWITCH ]											   				   		┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/
void TFT_SWITCH(unsigned int x)
{
	switch(x) {
	case 0:
		switch(tft_bit) {
		case TFT_16BIT:
			Put_Pixel = TFT0_16BITPutPixel;
			Put_Pixel_back = TFT1_16BITPutPixel;
			break;
		case TFT_24BIT:
		default:
			Put_Pixel = TFT0_24BITPutPixel;
			Put_Pixel_back = TFT1_24BITPutPixel;
			break;
		}
		WINCON0 &= ~(1<<23);
		return;
	case 1:
		switch(tft_bit) {
		case TFT_16BIT:
			Put_Pixel = TFT1_16BITPutPixel;
			Put_Pixel_back = TFT0_16BITPutPixel;
			break;
		case TFT_24BIT:
		default:
			Put_Pixel = TFT1_24BITPutPixel;
			Put_Pixel_back = TFT0_24BITPutPixel;
			break;
		}
		WINCON0 |= (1<<23);
		return;
	default:
		return;
	}
}

