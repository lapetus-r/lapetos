#include <include.h>
#include "include/kernel.h"	/* 대체경로 "/home/lapetus/바탕화면/lapetOS/src/include/kernel.h" */

/* Background Process Stack */
STACK background_stack[STACK_SIZE - 1];

/* Kernel Initialize */
void KernelInit(void)
{
	KerStatInit(); /* 커널 상태 초기화 */
	PCBListInit(); /* PCB 리스트 초기화 */
	ECBListInit(); /* ECB 리스트 초기화 */
	//ThreadInit(); /* 리눅스 커널을 이용한 쓰레드 초기화 [리눅스 포트 사용시 활성화] */
	procCreate(proc_background, &background_stack[STACK_SIZE - 1], PROC_CNT - 1);
	/* 백그라운드 프로세스 생성 */
}

/* Kernel Start */
void KernelStart(void)
{
	int listNum, flag = false;

	for(listNum = 0; listNum < PROC_CNT; listNum++){
		if(schedArr[listNum] == true && flag == false){
			flag = true; /* flag 값 설정 최우선 값 골라내기 위함 */
			nextPrio = listNum;
			highPCB = useArrPCB[nextPrio]; /* 최우선순위 PCB 지정 */
			curPCB = highPCB;
		}
	}
	kerStat = true; /* 커널 상태 실행으로 전환 */
	kernel_entry(); /* 문맥전환 */
}

/* Background Process */
void proc_background(void *data)
{
	for(;;){ /* background 프로세스 */

		TURN_OFF_INTERRUPT(); /* 인터럽트 비활성화 */
		backCnt ++;
		dummy();
		printf("idle process : %d\n", ticks);
		TURN_ON_INTERRUPT(); /* 인터럽트 활성화 */
	}
}

/* Scheduler */
void scheduler(void)
{
	int listNum, flag = false;
	
	TURN_OFF_INTERRUPT(); /* 인터럽트 비활성화 */
	for(listNum = 0; listNum < PROC_CNT; listNum++){
		if(schedArr[listNum] == true && flag == false){
			flag = true; /* flag 값 설정 최우선 값 골라내기 위함 */
			nextPrio = listNum;

			#if MODE == SCHED
				printf("[ticks: %d] \t[curPrio: %d] \t[nextPrio: %d]\t [schedArr:", ticks, curPrio, nextPrio);
				for(listNum = 0; listNum < PROC_CNT; listNum++){
					printf(" %d", schedArr[listNum]);
				}
				printf("]\n");
			#endif

			if(curPrio != nextPrio){ /* 현 우선순위가 다음 우선순위와 다르면 */
				highPCB = useArrPCB[nextPrio]; /* 최우선순위 PCB 지정 */
				kernel_soft_CS(); /* 문맥전환 */
			}
		}
	}
	TURN_ON_INTERRUPT(); /* 인터럽트 활성화 */
}

/* ISR */
void ISR(void)
{
	int listNum, flag = false;
	
	TURN_OFF_INTERRUPT(); /* 인터럽트 비활성화 */
	for(listNum = 0; listNum < PROC_CNT; listNum++){
		if(schedArr[listNum] == true && flag == false){
			flag = true; /* flag 값 설정 최우선 값 골라내기 위함 */
			nextPrio = listNum;

			#if MODE == SCHED
				printf("[ticks: %d] \t[curPrio: %d] \t[nextPrio: %d]\t [schedArr:", ticks, curPrio, nextPrio);
				for(listNum = 0; listNum < PROC_CNT; listNum++){
					printf(" %d", schedArr[listNum]);
				}
				printf("]\n");
			#endif

			if(curPrio != nextPrio){ /* 현 우선순위가 다음 우선순위와 다르면 */
				highPCB = useArrPCB[nextPrio]; /* 최우선순위 PCB 지정 */
				
				kernel_hard_CS(); /* 문맥전환 */
			}
		}
	}
	TURN_ON_INTERRUPT(); /* 인터럽트 활성화 */
}

/* Time Tick, 일정 주기마다 호출 */
void tick(void)
{
	if(kerStat == true){
		PCB *Pcb;
	
		TURN_OFF_INTERRUPT(); /* 인터럽트 비활성화 */
		ticks++;
		TURN_ON_INTERRUPT(); /* 인터럽트 활성화 */

		Pcb = listPCB;
		while(Pcb -> prio != PROC_CNT - 1){ /* 리스트를 순회하며 idle 프로세스 만날때까지 수행 */
	
		TURN_OFF_INTERRUPT(); /* 인터럽트 비활성화 */
			if(Pcb -> time > 0){
				Pcb -> time--; /* 틱 1 감소 */
				if(Pcb -> time == 0){
					schedArr[Pcb -> prio] = 1; /* 준비 상태로 전환 */
					Pcb -> stat = STAT_READY; /* 준비된 프로세스 대기상태로 전환 */
				}else if(Pcb -> time < 0){
					Pcb -> time = 0;
				}
			}		
			Pcb = Pcb -> nextPCB; /* 다음 PCB 값을 검사키 위해 */
			TURN_ON_INTERRUPT(); /* 인터럽트 활성화 */
		}
	}
}
