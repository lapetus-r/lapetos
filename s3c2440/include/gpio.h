#ifndef _GPIO_HEADER_
#define _GPIO_HEADER_

#define	LED_0			GPIO_bit(4)	// DEBUG LED
#define	LED_1			GPIO_bit(5)	// DEBUG LED
#define	LED_2			GPIO_bit(6)	// DEBUG LED
#define	LED_3			GPIO_bit(7)	// DEBUG LED

#define	LED_OFF			0
#define	LED_ON			1

void  GPIOInit(void); 				// GPIO ���� �ʱ�ȭ
void  GPIO_SetLED( int LedIndex, int value ); 	// GPIO �� ����� LED�� �����Ѵ�.

#endif //_GPIO_HEADER_
