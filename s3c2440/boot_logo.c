#include <include.h>
#define LCD_REG_INFO	0
#define CopyTo_SDRAM_BootLogo

// Full Color Bar Definitions.
// Top Set of Bars

static Word ColorTopBars[4][7]=
{
    {
        SYS_LT_GRAY,
        SYS_YELLOW,
        SYS_CYAN,
        SYS_GREEN,
        SYS_VIOLET,
        SYS_RED,
        SYS_BLUE,
    },
    {
        LT_GRAY_15BPP,
        YELLOW_15BPP,
        CYAN_15BPP,
        GREEN_15BPP,
        VIOLET_15BPP,
        RED_15BPP,
        BLUE_15BPP
    },
    {
        LT_GRAY_16BPP,
        YELLOW_16BPP,
        CYAN_16BPP,
        GREEN_16BPP,
        VIOLET_16BPP,
        RED_16BPP,
        BLUE_16BPP
    },
    {
        LT_GRAY_24BPP,
        YELLOW_24BPP,
        CYAN_24BPP,
        GREEN_24BPP,
        VIOLET_24BPP,
        RED_24BPP,
        BLUE_24BPP
    }
};

// Middle Set of Bars

static Word ColorMidBars[4][7]=
{
    {
        SYS_BLUE,
        SYS_GRAY_4,
        SYS_VIOLET,
        SYS_GRAY_4,
        SYS_CYAN,
        SYS_GRAY_4,
        SYS_LT_GRAY
    },
    {
        BLUE_15BPP,
        GRAY_4_15BPP,
        VIOLET_15BPP,
        GRAY_4_15BPP,
        CYAN_15BPP,
        GRAY_4_15BPP,
        LT_GRAY_15BPP
    },
    {
        BLUE_16BPP,
        GRAY_4_16BPP,
        VIOLET_16BPP,
        GRAY_4_16BPP,
        CYAN_16BPP,
        GRAY_4_16BPP,
        LT_GRAY_16BPP
    },
    {
        BLUE_24BPP,
        GRAY_4_24BPP,
        VIOLET_24BPP,
        GRAY_4_24BPP,
        CYAN_24BPP,
        GRAY_4_24BPP,
        LT_GRAY_24BPP
    }
};

// Bottom Set of Bars

static Word ColorBottomBars[4][8]=
{
    {
        SYS_DK_BLUE,
        SYS_WHITE,
        SYS_DK_VIOLET,
        SYS_GRAY_4,
        SYS_GRAY_0,
        SYS_GRAY_4,
        SYS_GRAY_8,
        SYS_GRAY_4
    },
    {
        BLUE_I_15BPP,
        WHITE_15BPP,
        BLUE_Q_15BPP,
        GRAY_4_15BPP,
        GRAY_0_15BPP,
        GRAY_4_15BPP,
        GRAY_8_15BPP,
        GRAY_4_15BPP
    },
    {
        BLUE_I_16BPP,
        WHITE_16BPP,
        BLUE_Q_16BPP,
        GRAY_4_16BPP,
        GRAY_0_16BPP,
        GRAY_4_16BPP,
        GRAY_8_16BPP,
        GRAY_4_16BPP
    },
    {
        BLUE_I_24BPP,
        WHITE_24BPP,
        BLUE_Q_24BPP,
        GRAY_4_24BPP,
        GRAY_0_24BPP,
        GRAY_4_24BPP,
        GRAY_8_24BPP,
        GRAY_4_24BPP
    }
};


//  �� �� : ������ ȭ�鿡 ColorBar�� �׸���.
int DrawColorBars(int iWidth, int iHeight, int bpp, char *FrameBuffer)
{
    int 	x,y,last,color;
    char 	*pBuffer;
    Word16 *pBuffer16;
    int 	iHeightTop;
    int 	iHeightMid;
    int 	iWidthTopMid;
    int 	iWidthBottom;
    int 	iWidthBottom2;

    // Set the Height of the top bars to 70% of screen
    iHeightTop = ((iHeight<<10)*0x2cc)>>20;

    // Set the Height of the middle bars to 8% of screen
    iHeightMid = iHeightTop + (((iHeight<<10)*0x51)>>20);

    // A little fixed point math to do a divide by 7
    // or Width of Top and Middle bars is Screen Width / 7.
    iWidthTopMid = ((iWidth<<10)*0x92)>>20;

    // More fixed point fun to do a divide by 6 or Width of bottom bars is Screen Width / 6.
    iWidthBottom = ((iWidth<<10)*0xaa)>>20;

    // Even more fun with 1/6/3 or Width of little bottom bars is Screen Width / 6 / 3.
    iWidthBottom2 = ((iWidth<<10)*0x38)>>20;

    pBuffer   = FrameBuffer;
    pBuffer16 = ( Word16* )FrameBuffer;

    for (y=0; y<iHeightTop; y++)
    {
        x=0;
        last = iWidthTopMid;
        for (color=0;color<7;color++)
        {
            if (color == 6)
            {
                last = iWidth;
            }
            for (; x<last; x++)
            {
                if (bpp == 8)
                {
                    pBuffer[x] = (Byte)ColorTopBars[0][color];
                }
                else if (bpp == 15)
                {
                    pBuffer16[x] = (Word16)ColorTopBars[1][color];
                }
                else if (bpp == 16)
                {
                    pBuffer16[x] = (Word16)ColorTopBars[2][color];
                }
                else if (bpp == 24)
                {
                    pBuffer[x*3] = (Byte)ColorTopBars[3][color];
                    pBuffer[x*3+1] = (Byte)(ColorTopBars[3][color] >> 8);
                    pBuffer[x*3+2] = (Byte)(ColorTopBars[3][color] >> 16);
                }
            }
            last = x + iWidthTopMid;
        }

        if (bpp == 8)
        {
           pBuffer += iWidth;
        }
        else if ((bpp == 16) || (bpp == 15))
        {
            pBuffer16 += iWidth;
        }
        else if (bpp == 24)
        {
            pBuffer += iWidth*3;
        }
    }

    for (; y<iHeightMid; y++)
    {
        x=0;
        last = iWidthTopMid;
        for (color=0;color<7;color++)
        {
            if (color == 6)
            {
                last = iWidth;
            }
            for (; x<last; x++)
            {
                 if (bpp == 8)
                {
                    pBuffer[x] = (Byte)ColorMidBars[0][color];
                }
                else if (bpp == 15)
                {
                    pBuffer16[x] = (Word16)ColorMidBars[1][color];
                }
                else if (bpp == 16)
                {
                    pBuffer16[x] = (Word16)ColorMidBars[2][color];
                }
                else if (bpp == 24)
                {
                    pBuffer[x*3] = (Byte)ColorMidBars[3][color];
                    pBuffer[x*3+1] = (Byte)(ColorMidBars[3][color] >> 8);
                    pBuffer[x*3+2] = (Byte)(ColorMidBars[3][color] >> 16);
                }
            }
            last = x + iWidthTopMid;
        }

        if (bpp == 8)
        {
            pBuffer += iWidth;
        }
        else if ((bpp == 16) || (bpp == 15))
        {
            pBuffer16 += iWidth;
        }
        else if (bpp == 24)
        {
            pBuffer += iWidth*3;
        }
    }

    for (; y<iHeight; y++)
    {
        x=0;
        last = iWidthTopMid;

        for (color=0;color<8;color++)
        {
            if (color == 7)
            {
                last = iWidth;
            }
            for (; x<last; x++)
            {
                if (bpp == 8)
                {
                    pBuffer[x] = (Byte)ColorBottomBars[0][color];
                }
                else if (bpp == 15)
                {
                    pBuffer16[x] = (Word16)ColorBottomBars[1][color];
                }
                else if (bpp == 16)
                {
                    pBuffer16[x] = (Word16)ColorBottomBars[2][color];
                }
                else if (bpp == 24)
                {
                    pBuffer[x*3] =   (Byte)(ColorBottomBars[3][color]);
                    pBuffer[x*3+1] = (Byte)(ColorBottomBars[3][color] >> 8);
                    pBuffer[x*3+2] = (Byte)(ColorBottomBars[3][color] >> 16);
                }
            }
            if ((color > 2) && (color < 6))
            {
                last = x + iWidthBottom2;
            }
            else
            {
                last = x + iWidthBottom;
            }
        }
        if (bpp == 8)
        {
            pBuffer += iWidth;
        }
        else if ((bpp == 16) || (bpp == 15))
        {
            pBuffer16 += iWidth;
        }
        else if (bpp == 24)
        {
            pBuffer += iWidth*3;
        }
    }

    return(0);
}

//  �� �� : RGB ���� 16 ��Ʈ 565 ���� ����Ÿ�� �ٲ۴�.
Word16	RGB2PIXEL565( int r, int g, int b )
{
	return ((((r) & 0xF8) << 8) | (((g) & 0xFC ) << 3) | (((b) & 0xF8 ) >> 3));
}

//  �� �� : SDRAM �޸𸮿� ����� BMP �̹����� ǥ���Ѵ�.

Word32 ImageDisplay( unsigned int src, unsigned int dst )
{
	int			LoopX, LoopY;
	int			LineByteSize;
	char		*pBitmapDataRGB;
	char		*pData;
	char 		*pBmpBitmap;
	Word16		*pSetBitmap;
	TBMPHEAD	*pBmpHeader = ( TBMPHEAD * )dst;

	pBmpBitmap	 = &pBmpHeader->biPixelData;
	LineByteSize = pBmpHeader->biWidth * 3;
	LineByteSize = (LineByteSize+3) & ( ~3 );

	// BMP �̹��� ������ ǥ���Ѵ�.
	printf("  File  Size  -  %d Bytes\n", pBmpHeader->bfSize);
	printf("  Image Size  -  %d x %d\n" , pBmpHeader->biWidth, pBmpHeader->biHeight);
	printf("\n");

	pData = ( char * ) src;
	
	// 0x4D42 = 'BM'
	if( pBmpHeader->bfType != 0x4D42 ) return 1;
		
	for( LoopY = pBmpHeader->biHeight-1; LoopY >= 0; LoopY-- )
	{
		pSetBitmap	= (Word16 *)( &pData[ LoopY * (pBmpHeader->biWidth * 2) ] );
		pBitmapDataRGB	= &pBmpBitmap[ ( ( pBmpHeader->biHeight-1 ) - LoopY ) * LineByteSize ];

		for( LoopX = 0; LoopX <= pBmpHeader->biWidth-1; LoopX++ )
		{
			// RGB ���� 16 ��Ʈ 565 ���� ����Ÿ�� �ٲ۴�.
			*pSetBitmap = RGB2PIXEL565( pBitmapDataRGB[2], pBitmapDataRGB[1], pBitmapDataRGB[0] );

			pSetBitmap++;
			pBitmapDataRGB++;
			pBitmapDataRGB++;
			pBitmapDataRGB++;
		}
	}

#if LCD_REG_INFO
	printf(	"bfType          =  0x%08X:0x%04X\n", &pBmpHeader->bfType         , pBmpHeader->bfType          );
	printf( "bfSize          =  0x%08X:0x%08X\n", &pBmpHeader->bfSize         , pBmpHeader->bfSize          );
	printf(	"bfReserved1     =  0x%08X:0x%04X\n", &pBmpHeader->bfReserved1    , pBmpHeader->bfReserved1     );
	printf(	"bfReserved2     =  0x%08X:0x%04X\n", &pBmpHeader->bfReserved2    , pBmpHeader->bfReserved2     );
	printf( "bfOffBits       =  0x%08X:0x%08X\n", &pBmpHeader->bfOffBits      , pBmpHeader->bfOffBits       );
	printf(	"biSize          =  0x%08X:0x%08X\n", &pBmpHeader->biSize         , pBmpHeader->biSize          );
	printf(	"biWidth         =  0x%08X:0x%08X\n", &pBmpHeader->biWidth        , pBmpHeader->biWidth         );
	printf(	"biHeight        =  0x%08X:0x%08X\n", &pBmpHeader->biHeight       , pBmpHeader->biHeight        );
	printf(	"biPlanes        =  0x%08X:0x%04X\n", &pBmpHeader->biPlanes       , pBmpHeader->biPlanes        );
	printf(	"biBitCount      =  0x%08X:0x%04X\n", &pBmpHeader->biBitCount     , pBmpHeader->biBitCount      );	//  (0,1,4,6,16,24,32)
	printf(	"biCompression   =  0x%08X:0x%08X\n", &pBmpHeader->biCompression  , pBmpHeader->biCompression   );	// (BI_RGB,BI_RLE8,BI_RLE4,BI_BITFIELDS,BI_JPEG,BI_PNG)
	printf(	"biSizeImage     =  0x%08X:0x%08X\n", &pBmpHeader->biSizeImage    , pBmpHeader->biSizeImage     );
	printf(	"biXPelsPerMeter =  0x%08X:0x%08X\n", &pBmpHeader->biXPelsPerMeter, pBmpHeader->biXPelsPerMeter );
	printf(	"biYPelsPerMeter =  0x%08X:0x%08X\n", &pBmpHeader->biYPelsPerMeter, pBmpHeader->biYPelsPerMeter );
	printf(	"biClrUsed       =  0x%08X:0x%08X\n", &pBmpHeader->biClrUsed      , pBmpHeader->biClrUsed       );
	printf(	"biClrImportant  =  0x%08X:0x%08X\n", &pBmpHeader->biClrImportant , pBmpHeader->biClrImportant  );
	printf(	"biPixelData     =  0x%08X:0x%02X\n", pBmpBitmap		      	  , pBmpBitmap[0]  				);
	printf(	"biPixelData     =  0x%08X:0x%02X\n", pBmpBitmap    		      , pBmpBitmap[1]  				);
	printf(	"biPixelData     =  0x%08X:0x%02X\n", pBmpBitmap    		      , pBmpBitmap[2]  				);
	printf(	"biPixelData     =  0x%08X:0x%02X\n", pBitmapDataRGB         	  , pBitmapDataRGB[0]  			);
	printf(	"biPixelData     =  0x%08X:0x%02X\n", pBitmapDataRGB    		  , pBitmapDataRGB[1]  			);
	printf(	"biPixelData     =  0x%08X:0x%02X\n", pBitmapDataRGB    		  , pBitmapDataRGB[2]  			);
	printf(	"LineByteSize    =  %d\n"           , LineByteSize                                              );
#endif

	return 0;
}

// ���� : TFT-LCD �ʱ�ȭ �� ��Ʈ�ΰ��� ȭ�鿡 ����Ѵ�.

void lcd_init(void)
{
	char	*FrameBuffer;   
	int		fb_size,iRet;

	LCD_LCDCON1 = LCDCON1_TFT16BPP |
				  LCDCON1_TFT 	   |
				  LCDCON1_CLKVAL(0x05);

	LCD_LCDCON2 = LCDCON2_VBPD(LCD_VBACKPORCH)  |
				  LCDCON2_LINEVAL(LCD_YRES-1)   |
				  LCDCON2_VFPD(LCD_VFRONTPORCH) |
				  LCDCON2_VSPW(LCD_VSYNCWIDTH);

	LCD_LCDCON3 = LCDCON3_HBPD(LCD_HBACKPORCH)  |
				  LCDCON3_HOZVAL(LCD_XRES-1)    |
				  LCDCON3_HFPD(LCD_HFRONTPORCH);

	LCD_LCDCON4 = LCDCON4_HSPW(LCD_HSYNCWIDTH)  |
				  LCDCON4_MVAL(0);

	LCD_LCDCON5 = LCDCON5_FRM565    			|
				  LCDCON5_INVVLINE				|
				  LCDCON5_INVVFRAME				|				  
				  LCDCON5_HWSWP;

	LCD_LPCSEL	= LPCSEL_VALUE;

	GPCCON = 0xAAAA56A9;
	GPCUP  = 0xFFFFFFFF;
	GPDCON = 0xAAAAAAAA;
	GPDUP  = 0xFFFFFFFF;

	LCD_LCDSADDR1 = (S3C24X0_FB_BASE) >> 1;
	LCD_LCDSADDR2 = (S3C24X0_FB_BASE + ((LCD_XRES * LCD_YRES * LCD_BPP )/8)) >> 1;	
	LCD_LCDSADDR3 = OFFSIZE(0) | PAGEWIDTH(LCD_XRES);

	LCD_LCDCON1	 |= LCDCON1_ENVID;	// ENVID Enable
	
	
#if LCD_REG_INFO
	printf("LCD_LCDCON1   [ 0x%08X ]\n", LCD_LCDCON1	);
	printf("LCD_LCDCON2   [ 0x%08X ]\n", LCD_LCDCON2	);
	printf("LCD_LCDCON3   [ 0x%08X ]\n", LCD_LCDCON3	);
	printf("LCD_LCDCON4   [ 0x%08X ]\n", LCD_LCDCON4	);
	printf("LCD_LCDCON5   [ 0x%08X ]\n", LCD_LCDCON5	);
	printf("LCD_LCDSADDR1 [ 0x%08X ]\n", LCD_LCDSADDR1	);
	printf("LCD_LCDSADDR2 [ 0x%08X ]\n", LCD_LCDSADDR2	);
	printf("LCD_LCDSADDR3 [ 0x%08X ]\n", LCD_LCDSADDR3	);
	printf("\n");	
#endif 

	fb_size = (LCD_XRES * LCD_YRES * LCD_BPP )/8;
	FrameBuffer = (void *) S3C24X0_FB_BASE;
	memset( (char *) FrameBuffer, 0, fb_size);


#if LCD_REG_INFO
	// ������� ���� ȭ�� �̴�. 
	DrawColorBars(LCD_XRES, LCD_YRES, LCD_BPP, (char *)FrameBuffer);
#else
	// �÷��ÿ� �ִ� BMP �̹��� ����Ÿ�� SDRAM �޸𸮷� �����Ѵ�.
	printf("Copy Init Image .....\n" );
	iRet = CopyTo_SDRAM_BootLogo( DEFAULT_RAM_WORK_START  );
	if( iRet )
	{
		// �޷θ��� �ִ� �̹��� ����Ÿ�� Ư�� �޸𸮷� �����Ѵ�.
	    	if ( ImageDisplay( S3C24X0_FB_BASE, DEFAULT_RAM_WORK_START ) )
	    	{
            		printf("   Fail!!! \n" );
					return;
			}
	}
	printf("\n" );
#endif

	return;
}
