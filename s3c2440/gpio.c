#include <s3c2440.h>
#include <gpio.h>

// ���� : GPIO �� �ʱ�ȭ �Ѵ�.
void GPIOInit(void)
{
//	unsigned long val;

	// i2c ���� ��Ʈ�� �ʱ�ȭ �Ѵ�.
        GPECON |= ( 0x2 <<30 | 0x2 << 28 );
}

// ���� : GPIO �� ����� LED�� �����Ѵ�. 
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
