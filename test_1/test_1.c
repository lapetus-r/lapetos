/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃			  														  lapetOS			   													   ┃
┃				 						 [ General Purpose Kernel for Embedded System ]									   ┃
┃			  																   																	   ┃
┃			  							  					SangMyung University									   					   ┃
┃			  							  				  Computer Science Major												       ┃
┃			  																				   													   ┃
┃					  					  Made By: Yoo Sang-Gi / Park Il-Kwon, 2011-2012							  	   ┃
┃			  											 	 File Name: test_1.c	 													   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

#include <include.h>
#include "../src/include/kernel.h"	/* 대체경로 "/home/lapetus/바탕화면/lapetOS/src/include/kernel.h"	*/

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃				 												 [ Process Stack ]														   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

STACK stktop1[STACK_SIZE - 1];
STACK stktop2[STACK_SIZE - 1];
STACK stktop3[STACK_SIZE - 1];
STACK stktop4[STACK_SIZE - 1];
STACK stktop5[STACK_SIZE - 1];

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃				 										 [ Method Prototype Declare ]												   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

void proc_1(void *data);
void proc_2(void *data);
void proc_3(void *data);
void proc_4(void *data);
void proc_5(void *data);
void methodCreate(void);

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃				 											 [ Target Method Create ]												   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

void methodCreate(void)
{
	procCreate(proc_2, &stktop2[STACK_SIZE - 1], 11);
	State(2,0);								//LCD우측하단에 Process 상태표시 2번째 프로세서 Create 출력
	TFT_Box_Select_Color(2, 3);	//LCD 2번째 프레임에 BackGround 칼라표시 3번 색상표시
	LCD_TIMER_Select(2);				//LCD 2번째 프레임에 사선표시

	procCreate(proc_3, &stktop3[STACK_SIZE - 1], 8);
	State(3,0);
	TFT_Box_Select_Color(3, 4);
	LCD_TIMER_Select(3);

	procCreate(proc_4, &stktop4[STACK_SIZE - 1], 6);
	State(4,0);
	TFT_Box_Select_Color(4, 5);
	LCD_TIMER_Select(4);

	procCreate(proc_5, &stktop5[STACK_SIZE - 1], 2);
	State(5,0);
	TFT_Box_Select_Color(5, 6);
	LCD_TIMER_Select(5);
}

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃				 													 [ Main Method ]														   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

int main(void)
{
	TFTLCD_Init(TFT_16BIT);											/* TFTLCD 초기화 */
	TFT_CLR(0);															/* LCD 화면 초기화(프레임버퍼 초기화)*/
	LCD_SQUARE();														/* LCD 전체 프레임셋 */
	LCD_LOGO();															/* LCD중앙 하단에 로고표시 */

	KernelInit();															/* 커널 초기화 */
	procCreate(proc_1, &stktop1[STACK_SIZE - 1], 0);		/* 프로세스 생성 */
	State(1,0);
	KernelStart();															/* 커널 구동 */

	return 0;
}

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃				 														 [ Dummy ]															   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

void dummy(void)
{
	lprintf("%d",ticks);
}

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃				 													 [ proc_1 Method ]													   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

void proc_1(void *data)
{
	int i=0;
	TFT_Box_Select_Color(1, 2);										/*LCD 1번째 프레임에 BackGround 칼라표시 */
	LCD_TIMER_Select(1);													/*LCD 1번째 프레임에 사선표시 */
	methodCreate();

	alarmResume(8, 24);
	alarmResume(6, 27);
	alarmResume(2, 30);
	alarmResume(0, 33);
	procSuspend(0);
	State(0,0);

	while(true){
		State(0,1);
		TFT_Box_Select_Color(1, 2);									/*LCD 1번째 프레임에 BackGround 칼라표시 */
		LCD_TIMER_Select(1);												/*LCD 1번째 프레임에 사선표시 */
		#if MODE == PRINT
			printf("[%d\t] Proc_1 is running!\n",ticks);
		#endif
		if(i == 10){
			procSuspend(2);
			procSuspend(0);
			alarmResume(11, 70);
		}
		i++;
	}
}

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃				 													 [ proc_2 Method ]													   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

void proc_2(void *data)
{
	TFT_Box_Select_Color(2, 3);
	int i=0;

	while(true){
		State(0,2);
		TFT_Box_Select_Color(2, 3);
		LCD_TIMER_Select(2);
		#if MODE == PRINT
			printf("[%d\t] Proc_2 is running!\n",ticks);
		#endif
		if(i == 10){
			State(0,3);
			procResume(8);
		}
		else if(i == 20){
			State(0,5);
			procResume(2);
		}
		i++;
	}
}

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃				 													 [ proc_3 Method ]													   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

void proc_3(void *data)
{
	TFT_Box_Select_Color(3, 4);
	int i=0;

	while(true){
		State(0,3);
		TFT_Box_Select_Color(3, 4);
		LCD_TIMER_Select(3);
		#if MODE == PRINT
			printf("[%d\t] Proc_3 is running!\n",ticks);	
		#endif
		if(i == 10){
			procSuspend(8);
		}
		else if(i == 20){
			procSuspend(8);
		}
		i++;
	}
}

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃				 													 [ proc_4 Method ]													   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

void proc_4(void *data)
{
	TFT_Box_Select_Color(4, 5);
	int i=0;

	while(true){
		State(0,4);
		TFT_Box_Select_Color(4, 5);
		LCD_TIMER_Select(4);
		#if MODE == PRINT
			printf("[%d\t] Proc_4 is running!\n",ticks);
		#endif
		if(i == 10){
			procSuspend(6);
		}
		i++;
	}
}

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃				 													 [ proc_5 Method ]													   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

void proc_5(void *data)
{
	TFT_Box_Select_Color(5, 6);
	int i=0;

	while(true){
		State(0,5);
		TFT_Box_Select_Color(5, 6);
		LCD_TIMER_Select(5);
		#if MODE == PRINT
			printf("[%d\t] Proc_5 is running!\n",ticks);
		#endif
		if(i == 10){
			procSuspend(2);
		}
		else if(i == 20){
			procSuspend(11);
			procSuspend(2);
		}
		i++;
	}
}

