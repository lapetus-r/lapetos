/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃			  														  lapetOS			   													   ┃
┃				 						 [ General Purpose Kernel for Embedded System ]									   ┃
┃			  																   																	   ┃
┃			  							  					SangMyung University									   					   ┃
┃			  							  				  Computer Science Major												       ┃
┃			  																				   													   ┃
┃					  					  Made By: Yoo Sang-Gi / Park Il-Kwon, 2011-2012							  	   ┃
┃			  											  File Name: semaphore.c	 												   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

#include <include.h>
#include "include/kernel.h"	/* 대체경로 "/home/lapetus/바탕화면/lapetOS/src/include/kernel.h" */

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃				 										 [ Semaphore Create ]															   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

ECB *semaCreate(int count)								/* 세마포어 생성 							*/
{
	ECB *Ecb;

	TURN_OFF_INTERRUPT();									/* 인터럽트 비활성화 					*/
	Ecb = freeECB;												/* 자유 ECB를 얻음 						*/
	if(freeECB != (ECB *)0){
		freeECB = (ECB *)freeECB -> eventPtr;
	}
	TURN_ON_INTERRUPT();									/* 인터럽트 활성화 						*/

	if(Ecb != (ECB *)0){
		Ecb -> type = EVENT_SEMAPHORE;				/* 이벤트 타입을 세마포어로 변경 	*/
		Ecb -> count = count;									/* 1이면 바이너리 세마포어			*/
		Ecb -> eventPtr = (void *)0;
		ECBInit(Ecb);												/* 해당 ECB를 초기화시킨다 			*/
	}
	else{
		#if MODE == DEBUG
			printf("semaCreate is failed.\n");
		#endif
	}
	return (Ecb);													/* 해당 ECB 반환 							*/
}

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃				 										 [ Semaphore Delete ]															   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

ECB *semaDelete(ECB *Ecb)								/* 세마포어 삭제 							*/
{
	if(Ecb -> type != EVENT_SEMAPHORE){
		return (Ecb);												/* 세마포어가 아니면 ECB 반환		*/
	}
	if(Ecb -> waitNum == 0){									/* 대기 프로세스가 없을때 수행 		*/

		TURN_OFF_INTERRUPT();								/* 인터럽트 비활성화 					*/
		Ecb -> type = EVENT_NULL;							/* 이벤트 타입을 널로 변경 			*/
		Ecb -> eventPtr = freeECB;
		freeECB = Ecb;											/* ECB 를 freeECB에 반환한다 		*/
		TURN_ON_INTERRUPT();								/* 인터럽트 활성화 						*/

		return ((ECB *)0);
	}
	else{
		#if MODE == DEBUG
			printf("semaDelete is failed.\n");
		#endif

		return (Ecb);												/* 대기 프로세스가 있으면 Ecb반환	*/
	}
}

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃				 										 [ Semaphore Pend ]															   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

void semaPend(ECB *Ecb)									/* 세마포어 획득 							*/
{
	if(Ecb == freeECB){
		#if MODE == DEBUG
			printf("not exist Ecb.\n");
		#endif

		return;
	}
	if(Ecb -> type != EVENT_SEMAPHORE){				/* 타입이 세마포어가 아니면 탈출	*/
		#if MODE == DEBUG
			printf("semaPend: event is not semaphore.\n");
		#endif

		return;
	}
	if(Ecb -> count > 0){										/* 카운트 값이 1 이상일때				*/

		TURN_OFF_INTERRUPT();								/* 인터럽트 비활성화 					*/
		Ecb -> count --;											/* 카운트 값을 1 감소시킨다 			*/
		TURN_ON_INTERRUPT();								/* 인터럽트 활성화						*/

		return;
	}
		TURN_OFF_INTERRUPT();								/* 인터럽트 비활성화 					*/
		curPCB -> stat = STAT_SEMAPHORE;			/* 해당 PCB 상태 세마포어로 바꿈	*/
		curPCB -> ecbPtr = Ecb;								/* 해당 PCB가 Ecb를 가리킴 			*/
		Ecb -> waitNum ++;									/* 세마포어 대기중 프로세스 증가	*/
		Ecb -> arrECB[curPCB -> prio] = 1;				/* ECB의 우선순위 테이블 값 1변경	*/
		schedArr[curPCB -> prio] = 0;						/* 해당 PCB의 우선순위 0으로 변경	*/
		TURN_ON_INTERRUPT();								/* 인터럽트 활성화 						*/
		
		scheduler();												/* 스케줄러 가동							*/

		#if LINUX_SEMA_TEST == true
			int i;
			for(i=0; i<10000000; i++){
			}
		#endif

		TURN_OFF_INTERRUPT();								/* 인터럽트 비활성화 					*/
		curPCB -> ecbPtr = (ECB *)0;						/* 해당 PCB가 널을 가리킴 			*/
		TURN_ON_INTERRUPT();								/* 인터럽트 활성화 						*/

		#if MODE == DEBUG
			printf("semaPend: pend from semaphore.\n");
		#endif
}

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃				 										 [ Semaphore Post ]															   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

void semaPost(ECB *Ecb)									/* 세마포어 반환 							*/
{
	PCB *Pcb;
	int listNum, flag = false;

	if(Ecb == freeECB){
		#if MODE == DEBUG
			printf("not exist Ecb.\n");
		#endif

		return;
	}
	if(Ecb -> type != EVENT_SEMAPHORE){				/* 타입이 세마포어가 아니면 탈출	*/
		#if MODE == DEBUG
			printf("semaPost: event is not semaphore.\n");
		#endif

		return;
	}
	if(Ecb -> waitNum > 0){

		TURN_OFF_INTERRUPT();								/* 인터럽트 비활성화 					*/
		Ecb -> waitNum --;										/* 세마포어 대기중 프로세스 감소	*/
		Pcb = useArrPCB[curPrio];
		Pcb -> stat = STAT_READY;							/* 해당 PCB를 준비상태로 변환 		*/
		Pcb -> ecbPtr = (ECB *)0;							/* 해당 PCB가 널을 가리킴 			*/
		for(listNum = 0; listNum < EVENT_CNT; listNum ++){
			if(Ecb -> arrECB[listNum] != 0 && flag == false){
				flag = true;
				schedArr[listNum] = 1;						/* 최우선순위 프로세스를 검색 		*/
			}
		}
		TURN_ON_INTERRUPT();								/* 인터럽트 활성화 						*/

		scheduler();												/* 스케줄러 가동 							*/

		#if LINUX_SEMA_TEST == true
			int i;
			for(i=0; i<10000000; i++){
			}
		#endif
	}
	if(Ecb -> count < EVENT_LIMIT){						/* ECB의 count값은 LIMIT보다 작음	*/

		TURN_OFF_INTERRUPT();								/* 인터럽트 비활성화 					*/
		Ecb -> count ++;
		TURN_ON_INTERRUPT();								/* 인터럽트 활성화 						*/

		#if MODE == DEBUG
			printf("semaPost: return the semaphore.\n");
		#endif
	}
}

