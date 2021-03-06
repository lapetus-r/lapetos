#ifndef _LCD_HEADER_
#define _LCD_HEADER_

#define S3C24X0_FB_BASE			0x33000000

#undef  EZ_S24XX_320X240
#define EZ_S24XX_480X272
#undef  EZ_S24XX_640X480


#ifdef EZ_S24XX_320X24						// 320x240x16bit
  #define LCD_XRES            320		// x resolition
  #define LCD_YRES            240		// y resolution
  #define LCD_BPP             16		// RGB 5-6-5 format
                                 		
  #define LCD_HFRONTPORCH     16		// Front Porch
  #define LCD_HBACKPORCH      16		// Back Porch
  #define LCD_HSYNCWIDTH      24		// Hsync Width
                                 		
  #define LCD_VFRONTPORCH     10		// Front Porch
  #define LCD_VBACKPORCH      33		// Back Porch
  #define LCD_VSYNCWIDTH      2			// Vsync Width
                                 		
  #define LPCSEL_VALUE        0xF84		// LPC3600 Disable (0x06 ?)
#endif

#ifdef EZ_S24XX_480X272					// 480x272x24bit
  #define LCD_XRES            480		// x resolition
  #define LCD_YRES            272		// y resolution
  #define LCD_BPP             16		// RGB 5-6-5 format
                                 		
  #define LCD_HFRONTPORCH     2			// Front Porch
  #define LCD_HBACKPORCH      2			// Back Porch
  #define LCD_HSYNCWIDTH      41		// Hsync Width
                                 		
  #define LCD_VFRONTPORCH     2			// Front Porch
  #define LCD_VBACKPORCH      2			// Back Porch
  #define LCD_VSYNCWIDTH      10			// Vsync Width
                                 		
  #define LPCSEL_VALUE        0xF84		// LPC3600 Disable (0x06 ?)
#endif

#ifdef EZ_S24XX_640X480					// 640x480x16bit
  #define LCD_XRES            640		// x resolition
  #define LCD_YRES            480		// y resolution
  #define LCD_BPP             16		// RGB 5-6-5 format
                                 		
  #define LCD_HFRONTPORCH     16		// Front Porch
  #define LCD_HBACKPORCH      16		// Back Porch
  #define LCD_HSYNCWIDTH      24		// Hsync Width
                                 		
  #define LCD_VFRONTPORCH     10		// Front Porch
  #define LCD_VBACKPORCH      33		// Back Porch
  #define LCD_VSYNCWIDTH      2			// Vsync Width

  #define LPCSEL_VALUE        0xF84		// LPC3600 Disable (0x06 ?)
#endif

// windows style BMP ���

typedef struct
{
 // BITMAPFILEHEADER
	Word16	bfType;
	Word32	bfSize;
	Word16	bfReserved1;
	Word16	bfReserved2;
	Word32	bfOffBits;
 // BITMAPINFOHEADER
	Word32	biSize;
	Word32	biWidth;
	Word32	biHeight;
	Word16	biPlanes;
	Word16	biBitCount;			//  (0,1,4,6,16,24,32)
	Word32	biCompression;		// (BI_RGB,BI_RLE8,BI_RLE4,BI_BITFIELDS,BI_JPEG,BI_PNG)
	Word32	biSizeImage;
	Word32	biXPelsPerMeter;
	Word32	biYPelsPerMeter;
	Word32	biClrUsed;
	Word32	biClrImportant;
	char    biPixelData;
} __attribute__ ((packed)) TBMPHEAD;

#endif
