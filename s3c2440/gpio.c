/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃			  														  lapetOS			   													   ┃
┃				 						 [ General Purpose Kernel for Embedded System ]									   ┃
┃			  																   																	   ┃
┃			  							  					SangMyung University									   					   ┃
┃			  							  				  Computer Science Major												       ┃
┃			  																				   													   ┃
┃					  					  Made by: Yoo Sang-Gi / Park Il-Kwon, 2011-2012							  	   ┃
┃			  											 	   File Name: gpio.c		 												   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

#include <s3c2440.h>
#include <gpio.h>


// 설명 : GPIO 를 초기화 한다.
void GPIOInit(void)
{
//	unsigned long val;

	// i2c 관련 포트를 초기화 한다.
        GPECON |= ( 0x2 <<30 | 0x2 << 28 );
}


// 설명 : GPIO 에 연결된 LED를 설정한다. 
void  GPIO_SetLED( int LedIndex, int value )
{
	if( value )
	{
		// led on
		switch( LedIndex )
		{
			case 0 : GPFDAT &= ~LED_0; break;
			case 1 : GPFDAT &= ~LED_1; break;
			case 2 : GPFDAT &= ~LED_2; break;
			case 3 : GPFDAT &= ~LED_3; break;			
		}
	}
	else
	{
		// led off
		switch( LedIndex )
		{
			case 0 : GPFDAT |= LED_0; break;
			case 1 : GPFDAT |= LED_1; break;
			case 2 : GPFDAT |= LED_2; break;
			case 3 : GPFDAT |= LED_3; break;
		}
	}
}

