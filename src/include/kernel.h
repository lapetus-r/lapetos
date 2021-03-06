#define KERNEL_VER 1 5 17 /* 커널 버전 */
#define PROC_CNT 16 /* 프로세스 갯수 */
#define EVENT_CNT 16 /* 이벤트 갯수 */
#define EVENT_LIMIT 32 /* 이벤트 한도 */
#define TIME_TICKS 1 /* 타임틱 주기 */
#define TURN_ON_INTERRUPT()	kernel_enable_int() /* 인터럽트 활성 */
#define TURN_OFF_INTERRUPT() kernel_disable_int() /* 인터럽트 비활성 */
#define STACK_SIZE	512 /* 스택 사이즈 */

#define ContextSW()	__asm__("swi") /* 문맥 전환 */

#define true 1
#define false 0

#define STAT_READY 0 /* 프로세스 상태: 준비 */
#define STAT_SEMAPHORE 1 /* 프로세스 상태: 세마포어 */
#define STAT_SUSPEND 2 /* 프로세스 상태: 일시정지 */

#define EVENT_NULL 0 /* 이벤트: 널 값 */
#define EVENT_SEMAPHORE 1 /* 이벤트: 세마포어 */

#define DEBUG 0	/* 디버그 모드 */
#define SCHED 1 /* 스케줄러 출력모드 */
#define PRINT 2 /* 프로세스 출력모드 */

#define LINUX_SEMA_TEST false /* 리눅스 세마포어 테스트 */

#define MODE PRINT /* 커널 구동모드 선택 */

/* Event Control Block */
typedef struct ecb {
	void *eventPtr; /* 이벤트 포인터 */
	int type; /* 이벤트 타입 */
	int count; /* 이벤트 카운트 */
	int waitNum; /* 대기중 이벤트 갯수 */
	int arrECB[EVENT_CNT]; /* 이벤트를 나타내는 배열 */
} ECB;

/* Process Control Block */
typedef struct pcb {
	STACK *stkPtr; /* 스택 포인터 */
	STACK *stkPtrBottom; /* 스택 하부를 가리키는 포인터 */
	ECB * ecbPtr; /* ECB를 가리키는 포인터 */
	int prio; /* 해당 프로세스 우선순위 */
	int stat; /* 해당 프로세스 상태 */
	int time; /* 해당 프로세스 딜레이 */
	long stkSize; /* 해당 프로세스 스택 사이즈 */
	struct pcb *nextPCB; /* 다음 PCB를 가리키는 구조체 포인터 */
	struct pcb *prevPCB; /* 이전 PCB를 가리키는 구조체 포인터 */
} PCB;

/* Global Variable Declare */
extern int enterISR;
extern int kerStat;
extern int curPrio, nextPrio, procNum;
extern int ticks;
extern int backCnt;
extern int schedArr[PROC_CNT];
extern STACK stktop[STACK_SIZE];

extern PCB *listPCB; /* 현재 생성되어 있는 프로세스 리스트의 PCB를 가리킴 */
extern PCB *curPCB; /* 현재 수행중인 프로세스의 PCB를 가리킴 */
extern PCB *highPCB; /* 최고 우선순위 프로세스의 PCB를 가리킴 */
extern PCB *freePCB; /* PCB의 자유리스트를 가리킴 */
extern PCB *useArrPCB[PROC_CNT]; /* 해당 PCB를 사용할 때 1, 사용하지 않을 때 0 */
extern PCB arrPCB[PROC_CNT]; /* PCB 초기화에 사용 */

extern ECB *freeECB; /* ECB의 자유리스트를 가리킴 */
extern ECB arrECB[EVENT_CNT];

/* Method Prototype Declare */
void debug(void);

STACK *PCBStackInit(void (*proc)(void *pd), STACK *stktop, void *data);

void kernel_soft_CS(void);
void kernel_hard_CS(void);
void kernel_entry(void);
void kernel_enable_int(void);
void kernel_disable_int(void);

void proc_background(void *data); /* idle 프로세스 */
void ThreadCreate(PCB *Pcb);

void StartInt(void);
void EndInt(void);
void KerStatInit(void);
void KernelInit(void);
void KernelStart(void);
void proc_background(void *data);
void procCreate(void (*proc)(void *pd), STACK *stktop, int prio);
void procDelete(int prio);
void procSuspend(int prio);
void procResume(int prio);
void alarmResume(int prio, int time);
void PCBInit(STACK *stktop, LONG stkSize, int prio);
void PCBListInit(void);
void ECBInit(ECB *evt);
void ECBListInit(void);
void ReadyListInit(void);
void scheduler(void);
void tick(void);
ECB *semaCreate(int count);
ECB *semaDelete(ECB *Ecb);
void semaPend(ECB *Ecb);
void semaPost(ECB *Ecb);
void dummy(void);
