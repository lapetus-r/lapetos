#include <include.h>
#include "include/kernel.h"	/* 대체경로 "/home/lapetus/바탕화면/lapetOS/src/include/kernel.h" */

/* Process Create */
void procCreate(void (*proc)(void *pd), STACK *stktop, int prio)
{
	STACK *Pcb;
	void *data = (void *) 0;

	if(useArrPCB[prio] == (PCB *)0){
		useArrPCB[prio] = (PCB *)1; /* 해당 prio 사용알림 */
		schedArr[prio] = 1;

		TURN_OFF_INTERRUPT(); /* 인터럽트 비활성화 */
		procNum ++;
		TURN_ON_INTERRUPT(); /* 인터럽트 활성화 */

		Pcb = (STACK *)PCBStackInit(proc, stktop, data); /* PCB 스택 초기화 */
		PCBInit(Pcb, 0, prio); /* PCB 초기화 */

		if(kerStat == true){
			scheduler(); /* 스케줄러 호출 */
		}
	}else{
	
		#if MODE == DEBUG
			printf("[%d]th proc is already create.\n", prio);
		#endif
	}
}

/* Process Delete */
void procDelete(int prio)
{
	PCB *Pcb;

	TURN_OFF_INTERRUPT(); /* 인터럽트 비활성화 */
	Pcb = useArrPCB[prio];
	if(schedArr[prio]){
		useArrPCB[prio] = (PCB *)0; /* useArrPCB[prio] 값 초기화 */
		schedArr[prio] = 0; /* schedArrPCB[prio] 값 초기화 */
		procNum --;
		Pcb -> stat = STAT_READY; /* 상태를 중지로 전환 */
		if(Pcb -> prevPCB == (PCB *)0){ /* 해당 PCB의 이전 PCB가 없으면 */
			Pcb -> nextPCB -> prevPCB = (PCB *)0; /* 다음 PCB의 이전PCB 값을 초기화	*/
			listPCB = Pcb -> nextPCB; /* 리스트가 PCB의 다음 PCB를 가리키도록 */
		}
		else{
			Pcb -> prevPCB -> nextPCB = Pcb -> nextPCB;
			/* 이전 PCB의 다음 PCB값을 현재 PCB의 다음 PCB값으로 설정 */
			Pcb -> nextPCB -> prevPCB = Pcb -> prevPCB;
			/* 다음 PCB의 이전 PCB값을 현재 PCB의 이전 PCB값으로 설정 */
		}
		Pcb -> nextPCB = freePCB; /* 자유 PCB 리스트에 매달림 */
		freePCB = Pcb;
		TURN_ON_INTERRUPT(); /* 인터럽트 활성화 */
		
		if(kerStat == true){
			scheduler(); /* 스케줄러 호출 */
		}
	}else{
		TURN_ON_INTERRUPT(); /* 인터럽트 활성화 */
		
		#if MODE == DEBUG
			printf("not exist [%d]th proc for delete.\n", prio);
		#endif
	}
}

/* Process Suspend */
void procSuspend(int prio)
{
	PCB *Pcb;
	
	TURN_OFF_INTERRUPT(); /* 인터럽트 비활성화 */
	Pcb = useArrPCB[prio];
	if(schedArr[prio]){
		schedArr[prio] = 0;
		Pcb -> stat = STAT_SUSPEND; /* 상태를 정지로 전환 */
		TURN_ON_INTERRUPT(); /* 인터럽트 활성화 */

		if(kerStat == true){
			scheduler(); /* 스케줄러 호출 */
		}
	}else{
		TURN_ON_INTERRUPT(); /* 인터럽트 활성화 */

		#if MODE == DEBUG
			printf("not exist [%d]th proc for suspend.\n", prio);
		#endif
	}
}

/* Process Resume */
void procResume(int prio)
{
	PCB *Pcb;

	TURN_OFF_INTERRUPT(); /* 인터럽트 비활성화 */
	Pcb = useArrPCB[prio];
	if(!schedArr[prio]){
		schedArr[prio] = 1;
		Pcb -> stat = STAT_READY; /* 상태를 준비로 전환 */
		TURN_ON_INTERRUPT(); /* 인터럽트 활성화 */

		if(kerStat == true){
			scheduler(); /* 스케줄러 호출 */
		}
	}else{
		TURN_ON_INTERRUPT(); /* 인터럽트 활성화 */

		#if MODE == DEBUG
			printf("not exist [%d]proc for resume.\n", prio);
		#endif
	}
}

/* Process Alarm Resume */
void alarmResume(int prio, int time) /* procSuspend 및 procDelete 이전에 호출해야 함 */
{
	if(useArrPCB[prio] != (PCB *)0){
		if(time > 0){
			PCB *Pcb;
			Pcb = useArrPCB[prio];

			TURN_OFF_INTERRUPT(); /* 인터럽트 비활성화 */
			Pcb -> time = time;
			TURN_ON_INTERRUPT(); /* 인터럽트 활성화 */
		}
		else{
		
			#if MODE == DEBUG
				printf("[%d]th proc delay is < 0.\n", prio);
			#endif
		}
	}else{
	
		#if MODE == DEBUG
			printf("not exist [%d]th proc for alarmResume.\n", prio);
		#endif
	}
}
