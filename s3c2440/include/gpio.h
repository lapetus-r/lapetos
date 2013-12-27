/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃			  														  lapetOS			   													   ┃
┃				 						 [ General Purpose Kernel for Embedded System ]									   ┃
┃			  																   																	   ┃
┃			  							  					SangMyung University									   					   ┃
┃			  							  				  Computer Science Major												       ┃
┃			  																				   													   ┃
┃					  					  Made By: Yoo Sang-Gi / Park Il-Kwon, 2011-2012							  	   ┃
┃			  											 	 File Name: gpio.h		 													   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/


#ifndef _GPIO_HEADER_
#define _GPIO_HEADER_

#define	LED_0			GPIO_bit(4)	// DEBUG LED
#define	LED_1			GPIO_bit(5)	// DEBUG LED
#define	LED_2			GPIO_bit(6)	// DEBUG LED
#define	LED_3			GPIO_bit(7)	// DEBUG LED

#define	LED_OFF			0
#define	LED_ON			1

void  GPIOInit(void); 				// GPIO 상태 초기화
void  GPIO_SetLED( int LedIndex, int value ); 	// GPIO 에 연결된 LED를 제어한다.

#endif //_GPIO_HEADER_

