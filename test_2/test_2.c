#include <include.h>
#include "../src/include/kernel.h"	/* 대체경로 "/home/lapetus/바탕화면/lapetOS/src/include/kernel.h"	*/

/* Process Stack */
STACK stktop1[STACK_SIZE - 1];
STACK stktop2[STACK_SIZE - 1];
STACK stktop3[STACK_SIZE - 1];


/* Global Variable Declare */
int var; /* 세마포어에 의해 보호될 전역변수 */
ECB *sema; /* 세마포어 포인터형 변수 */

/* Method Prototype Declare */
void proc_1(void *data);
void proc_2(void *data);
void proc_3(void *data);
void methodCreate(void);

/* Target Method Create */
void methodCreate(void)
{
	procCreate(proc_2, &stktop2[STACK_SIZE - 1], 9);
	procCreate(proc_3, &stktop3[STACK_SIZE - 1], 5);
}

/* Main Method */
int main(void)
{
	KernelInit(); /* 커널 초기화 */
	sema = semaCreate(1); /* 바이너리 세마포어 생성 */
	procCreate(proc_1, &stktop1[STACK_SIZE - 1], 0); /* 프로세스 생성 */
	KernelStart(); /* 커널 구동 */
	
	return 0;
}

/* proc_1 Method */
void proc_1(void *data)
{
	methodCreate();
	procSuspend(5);
	procSuspend(0);
	
	for(;;){
	}
}

/* proc_2 Method */
void proc_2(void *data)
{
	int x = 1;
	int y = 2;
	int i = 0;
	
	for(;;i++){
		//semaPend(sema);
		var = x;

		if(i == 200){
			procResume(5);
		}
		x = y;
		y = var;
		//semaPost(sema);
		#if MODE == PRINT
			printf("%d: proc_2 var: %d\n",i ,var);
		#endif
	}
}

/* proc_3 Method */
void proc_3(void *data)
{
	int z = 3;
	int i = 0;
	
	for(;;i++){
		//semaPend(sema);
		var = z;
		//semaPost(sema);

		if(i == 200){
			procSuspend(5);
		}

		#if MODE == PRINT
			printf("%d: proc_3 var: %d\n",i ,var);
		#endif
	}
}
