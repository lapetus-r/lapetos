#include <include.h>
#include "include/kernel.h"	/* 대체경로 "/home/lapetus/바탕화면/lapetOS/src/include/kernel.h" */

/* Global Variable Declare */
int enterISR;
int kerStat;
int curPrio, nextPrio, procNum;
int ticks;
int backCnt;
int schedArr[PROC_CNT];
STACK stktop[STACK_SIZE];

PCB *listPCB; /* 현재 생성되어 있는 프로세스 리스트의 PCB를 가리킴	*/
PCB *curPCB; /* 현재 수행중인 프로세스의 PCB를 가리킴 */
PCB *highPCB; /* 최고 우선순위 프로세스의 PCB를 가리킴 */
PCB *freePCB; /* PCB의 자유리스트를 가리킴 */
PCB *useArrPCB[PROC_CNT]; /* 해당 PCB를 사용할 때 1, 사용하지 않을 때 0 */
PCB arrPCB[PROC_CNT]; /* PCB 초기화에 사용 */

ECB *freeECB; /* ECB의 자유리스트를 가리킴 */
ECB arrECB[EVENT_CNT];

/* Kernel Stat Initialize */
void KerStatInit(void)
{
	int i;
	ticks =0;
	kerStat = false;
	curPrio = 0;
	nextPrio = 0;
	backCnt = 0;
	curPCB = (PCB *)0;
	highPCB = (PCB *)0;
	for(i=0; i<PROC_CNT; i++){
		schedArr[i] = 0;
	}

	#if MODE == DEBUG
		printf("kerStat have been initialized.\n");
	#endif
}

/* Process Control Block Initialize */
void PCBInit(STACK *stktop, LONG stkSize, int prio)
{
	PCB *Pcb;
	Pcb = freePCB;

	TURN_OFF_INTERRUPT(); /* 인터럽트 비활성화 */
	freePCB = Pcb -> nextPCB; /* 자유리스트로부터 PCB 획득 */
	TURN_ON_INTERRUPT(); /* 인터럽트 활성화 */

	Pcb -> stkPtr = stktop;
	Pcb -> prio = prio;
	Pcb -> stat = STAT_READY;
	Pcb -> time = 0;
	// ThreadCreate(Pcb); /* 리눅스 포트 사용시 활성화 */

	TURN_OFF_INTERRUPT(); /* 인터럽트 비활성화 */
	useArrPCB[prio] = Pcb;
	Pcb -> nextPCB = listPCB; /* 획득한 PCB를 리스트에 연결 */
	Pcb -> prevPCB = (PCB *)0;	
	if(listPCB != (PCB *)0)
		listPCB -> prevPCB = Pcb;
	listPCB = Pcb;
	TURN_ON_INTERRUPT(); /* 인터럽트 활성화 */

	#if MODE == DEBUG
		printf("[%d]th prio's PCB have been initialized.\n", prio);
	#endif
}

/* Process Control Block List Initialize */
void PCBListInit(void)
{
	int i;
	PCB *prev, *next;
	listPCB = (PCB *)0;
	prev = &arrPCB[0];
	next = &arrPCB[1];
	for(i=0; i<PROC_CNT; i++){ /* prev와 next를 증가시켜주며 연결 */
		useArrPCB[i] = (PCB *)0; /* 해당 PCB를 사용할 때 1, 사용하지 않을 때 0 */
		prev -> nextPCB = next;
		prev++;
		next++;
	}
	prev -> nextPCB = (PCB *)0;
	freePCB = &arrPCB[0]; /* 자유리스트가 arrPCB를 가리키도록 함 */
	
	#if MODE == DEBUG
		printf("PCBList have been initialized.\n");
	#endif
}

/* Event Control Block Initialize */
void ECBInit(ECB *Ecb) /* PCBInit과 같은 방식으로 동작한다 */
{
	int i;
	int *ptr;
	Ecb -> waitNum = 0;
	ptr = &Ecb -> arrECB[0];
	for(i=0; i<EVENT_CNT; i++){
		*ptr++ = 0x00;
	}
	
	#if MODE == DEBUG
		printf("ECB have been initialized.\n");
	#endif
}

/* Event Control Block List Initialize */
void ECBListInit(void) /* ECBListInit과 같은 방식으로 동작한다 */
{
	int i;
	ECB *prev, *next;
	prev = &arrECB[0];
	next = &arrECB[1];
	for(i=0; i<EVENT_CNT; i++){
		prev -> type = EVENT_NULL;
		prev -> eventPtr = next;
		prev++;
		next++;
	}
	prev -> type = EVENT_NULL;
	prev -> eventPtr = (ECB *)0;
	freeECB = &arrECB[0];

	#if MODE == DEBUG
		printf("ECBList have been initialized.\n");
	#endif
}
