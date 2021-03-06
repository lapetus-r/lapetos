#include<include.h>

// 설명 : GPIO의 일종으로 SW40*키를 누름으로써 화면의 출력을 하는 함수

void test_key(void)	
{
	printf("Test_Key()\n\r");

/*
		EINT0_GPF0	SW401
		EINT0_GPF0	SW402
		EINT0_GPF0	SW403
		EINT0_GPF0	SW404
*/

	while(1){
		delay_cputimeconsume(100000);
		
		if(0 ==(GPFDAT & 0X1))
			{
				printf("SW401 is pressed!\n\r");
			}

		if(0 ==(GPFDAT & 0X2))
			{
				printf("SW402 is pressed!\n\r");
			}

		if(0 ==(GPFDAT & 0X4))
			{
				printf("SW403 is pressed!\n\r");
			}

		if(0 ==(GPFDAT & 0X8))
			{
				printf("SW404 is pressed!\n\r");
				break;
			}
	}
}
