#include<include.h>

// cpu의 시간지연을 시키는 함수 
void delay_cputimeconsume(volatile unsigned int countval)		
{
	for(;countval > 0; countval --);
}

void reset_software(void)
{
	SWIRST = 0x533C2443;
	printf("gg");
}
