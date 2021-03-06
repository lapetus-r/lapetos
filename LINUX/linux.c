#include    <stdio.h>
#include    <stdlib.h>
#include    <stdarg.h>
#include    <sys/time.h>
#include    <sys/resource.h>
#include    <sys/sem.h>
#include    <signal.h>
#include    <sched.h>
#include    <assert.h>
#include    <linux/unistd.h>
#include    <asm/unistd.h>
#include    <string.h>
#include    <sys/time.h>

#include "linux.h" /* "/home/lapetus/바탕화면/lapetOS/proc_linux/linux.h" */
#include "../src/include/kernel.h" /* "/home/lapetus/바탕화면/lapetOS/src/include/kernel.h" */

/* Variable Declare */
int parentThread;
int schedCONT, schedule;
int suspend[PROC_CNT], thread[PROC_CNT];
int intCONT, interrupt;
sigset_t intSigSet, schedSigSet, o_intSigSet, o_schedSigSet;
BOOLEAN criticalSectionFlag = true;
BOOLEAN intFlag = false;
BOOLEAN schedFlag = false;

typedef int (*PROC_START_POINT)(void*);

int sema; /* 세마포어 변수 */

/* Semaphore Create, Pend, Post */
void linuxsemaCreate(int *sema)
{
	*sema = semget(1, 1, IPC_CREAT | 0666);
	semctl(*sema, 0, SETVAL, 1);
}

void linuxsemaPend(int *sema)
{
	struct sembuf op;
	op.sem_num = 0;
	op.sem_flg = 0;
	op.sem_op = -1;
}

void linuxsemaPost(int *sema)
{
	struct sembuf op;
	op.sem_num = 0;
	op.sem_flg = 0;
	op.sem_op = 1;
}

/* Interrupt Enable, Disable */
void EnableInt(void)
{
	if(criticalSectionFlag == false){
		if(syscall(__NR_gettid) != intCONT){
			sigprocmask(SIG_UNBLOCK, &intSigSet, NULL);
		}
		criticalSectionFlag = true;
	}
}

void DisableInt(void)
{
	if(criticalSectionFlag == true){
		if(syscall(__NR_gettid) != intCONT){
			sigprocmask(SIG_BLOCK, &intSigSet, NULL);
		}
		criticalSectionFlag = false;
	}
}

/* Context Switching */
void CtxSwfromSched(void)
{
	syscall(__NR_tkill, schedule, schedCONT); /* 시그널 보냄 */
}

void CtxSwfromISR(void)
{
	syscall(__NR_tkill, schedule, schedCONT); /* 시그널 보냄 */
}

/* Kernel Stop */
void KernelBreaker(int ctrl)
{
	if(ctrl == SIGTSTP || ctrl == SIGINT){ /* ctrl + c 누를시 구동 정지 */
		printf("Shutdown\n");
		exit(0);
	}
}

/* Sched Handler, ISR Handler */
void SchedFlagHandler(int para)
{
	schedFlag = true; /* PScheduler 재가동 */
}

void IntFlagHandler(int para)
{
	intFlag = true;	/* ISR 재가동 */
}

/* Thread Scheduler */
void PScheduler(int parameter)
{
	char temp[256];
	int curThreadPrio, nextThreadPrio;

	while(true){
		sigprocmask(SIG_BLOCK, &schedSigSet, &o_schedSigSet); /* 시그널 블럭 */

		while(!schedFlag){
			sigsuspend(&o_schedSigSet);	/* 시그널 대기 상태 */
		}
		sigprocmask(SIG_UNBLOCK, &schedSigSet, NULL); /* 시그널 도착시 언블럭 */
		schedFlag = false;

		linuxsemaPend(&sema);
		curThreadPrio = curPrio;
		nextThreadPrio = nextPrio;
		curPCB = highPCB; /* 현재 PCB를 최우선순위 PCB로 전환 */
		curPrio = nextPrio;	/* 현재 우선순위를 최우선순위로 전환 */
		if((curThreadPrio != nextThreadPrio) && suspend[curThreadPrio] == 0){
			suspend[curThreadPrio] = 1;	/* 1이면 정지상태 */
			syscall(__NR_tkill, thread[curThreadPrio], SIGSTOP);
		}
		/* 현재 스레드 정지시킴 */
		if(suspend[nextThreadPrio] == 1){
			syscall(__NR_tkill, thread[nextThreadPrio], schedCONT);
			suspend[nextThreadPrio] = 0; /* 0이면 구동상태 */
		}
		/* 최우선순위 스레드 구동시킴 */
		linuxsemaPost(&sema);
	}
}

/* ISR */
void ISR(int parameter)
{
	char temp[256];

	while(true){
		sigprocmask(SIG_BLOCK, &intSigSet, &o_intSigSet); /* 시그널 블럭 */

		while(!intFlag){
			sigsuspend(&o_intSigSet); /* 시그널 대기 상태 */
		}
		printf("진입!!\n");
		sigprocmask(SIG_UNBLOCK, &intSigSet, NULL);	/* 시그널 도착시 언블럭 */
		intFlag == false;

		linuxsemaPend(&sema);
		tickMethod(); /* 타임 틱 인터럽트 수행 */
		linuxsemaPost(&sema);
	}
}

/* Scheduluer, ISR initialize */
void ThreadInit(void)
{
	char temp[256];
	parentThread = syscall(__NR_gettid);

	schedCONT = SIGCONT; /* SIGCONT를 schedCONT에 등록 */

	if(signal(schedCONT, SchedFlagHandler) != 0){
		#if MODE == DEBUG
			printf("signal error!\n"); /* schedCONT신호시 SchedFlagHandler호출 */
		#endif
	}
	if(sigemptyset(&schedSigSet) != 0){
		#if MODE == DEBUG
			printf("emptyset error!\n"); /* sigemptyset에 schedSigSet 등록 */
		#endif
	}
	if(sigaddset(&schedSigSet, schedCONT) != 0){
		#if MODE == DEBUG
			printf("signal add error!\n"); /* schedSigSet에 schedCONT 등록 */
		#endif
	}
	if(sigemptyset(&intSigSet) != 0){
		#if MODE == DEBUG
			printf("emptyset error!\n"); /* sigemptyset에 intSigSet 등록 */
		#endif
	}
	if(sigaddset(&intSigSet, schedCONT) != 0){
		#if MODE == DEBUG
			printf("signal add error!\n"); /* intSigSet에 schedCONT 등록 */
		#endif
	}

	intCONT = SIGUSR1; /* SISGUSR1을 intCONT에 등록, 커널버전 2.6.x에서 미지원 */

	if(signal(intCONT, IntFlagHandler) != 0){
		#if MODE == DEBUG
			printf("1signal error!\n");	/* intCONT 신호시 intFlagHandler 호출 */
		#endif
	}
	if(sigaddset(&intSigSet, intCONT) != 0){
		#if MODE == DEBUG
			printf("signal add error!\n"); /* intSigSet에 intCONT 등록 */
		#endif
	}
	if(signal(SIGINT, KernelBreaker) != 0){
		#if MODE == DEBUG
			printf("2signal error!\n");	/* KernelBreaker 신호 보낼시 SIGINT 구동 */
		#endif
	}
	if(signal(SIGTSTP, KernelBreaker) != 0){
		#if MODE == DEBUG
			printf("3signal error!\n");	/* KernelBreaker 신호 보낼시 SIGTSTP 구동 */
		#endif
	}

	linuxsemaCreate(&sema);

	interrupt = clone((PROC_START_POINT)ISR, malloc(STACK_SIZE)+STACK_SIZE, CLONE_FS | CLONE_FILES | CLONE_SIGHAND |CLONE_VM, NULL);		/* interrupt 쓰레드 생성 */
	syscall(__NR_tkill, interrupt, SIGSTOP);
	schedule = clone((PROC_START_POINT)PScheduler, malloc(STACK_SIZE)+STACK_SIZE, CLONE_FS | CLONE_FILES | CLONE_SIGHAND |CLONE_VM, NULL);		/* schedule 쓰레드 생성 */
	syscall(__NR_tkill, schedule, SIGSTOP);

	tickMethod = tick; /* intMethod 함수 호출시 tick 함수 호출 */
	sched_yield(); /* 스케줄링 양도 */
}

/* Thread Create */
void ThreadCreate(PCB * Pcb)
{
	TURN_OFF_INTERRUPT(); /* 인터럽트 비활성화 */
	suspend[Pcb -> prio] = 1;
	thread[Pcb->prio] = clone((PROC_START_POINT) *(Pcb -> stkPtr), malloc(STACK_SIZE)+STACK_SIZE, CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, (void *) *(Pcb->stkPtr + 1));
	/* clone을 이용한 쓰레드 생성 */
	syscall(__NR_tkill, thread[Pcb->prio], SIGSTOP);
	/* 해당 쓰레드 생성과 동시에 정지 */
	TURN_ON_INTERRUPT(); /* 인터럽트 활성화 */
}

/* Kernel Sleep */
void KernelSleep(void)
{
	struct timespec req, rem;
	req.tv_sec = 0;
	req.tv_nsec = 10000000;
	nanosleep(&req, &rem); /* 커널 슬립 */
}

/* Time Tick initialize */
void TimeTickInit(void)
{
	struct itimerval timer;
	signal(SIGALRM, TimeTickSignal);
	timer.it_interval.tv_sec = (1000000 / TIME_TICKS) / 1000000;
	timer.it_interval.tv_usec = (1000000 / TIME_TICKS) % 1000000;
	timer.it_value = timer.it_interval;
	setitimer(ITIMER_REAL, &timer, NULL);	/* 타이머 가동, 타임 틱을 위함 */
}

/* PCB Stack initialize */
STACK *PCBStackInit(void (*proc)(void *pd), STACK *stktop)
{
	STACK *stack;
	stack = (STACK *) stktop;
	*--stack = (unsigned long) proc;
	return stack; /* 스택을 초기화하고 stack 주소를 리턴 */
}

/* Time Tick Signal */
void TimeTickSignal(int parameter)
{
	tickMethod(); /* tick() 함수 호출 */
	scheduler(); /* 스케줄러 호출 */
	//syscall(__NR_tkill, interrupt, SIGCONT);
	/* 타임틱으로 인한 ISR구동, 리눅스 커널 2.6.x에서는 구동되지 않으므로 다른방식으로 구현 */
}

/* Kernel Start */
void ThreadStart(void)
{
	TimeTickInit(); /* 타임틱 시그널 보냄 */
	syscall(__NR_tkill, schedule, schedCONT); /* 최초 시그널 보냄 */
	while(true){
		KernelSleep(); /* 커널 슬립 */
	}
}
