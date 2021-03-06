#define svc_stack	0x30300000				/* SVC ��� ���� ����							*/
#define irq_stack	0x30380000				/* IRQ ��� ���� ����								*/

.global	_ram_entry
.global	kernel_init
.global	kernel_soft_CS
.global	kernel_hard_CS
.global	kernel_tick
.global	kernel_entry
.global	kernel_enable_int
.global	kernel_disable_int

/*
����������������������������������������������������������������������������������������������
��				 													 [ Ram Entry ]															   ��
����������������������������������������������������������������������������������������������
*/

_ram_entry:											/* �� ��Ʈ��: ��Ʈ�δ����� �ּҸ� ����	*/

	b		kernel_init
	b		_ram_entry
	b		kernel_soft_CS
	b		kernel_tick
	b		kernel_hard_CS
	b		kernel_entry
	b		kernel_enable_int
	b		kernel_disable_int

/*
����������������������������������������������������������������������������������������������
��				 												 [ kernel Initialize ]														   ��
����������������������������������������������������������������������������������������������
*/

kernel_init:

	msr		cpsr_c, #0x40|0x12			/* IRQ ��� ���� �� stack pointer �ʱ�ȭ		*/
	ldr			sp, =irq_stack
	msr		cpsr_c, #0x40|0x13			/* SVC ��� ���� �� stack pointer �ʱ�ȭ		*/
	ldr			sp, =svc_stack
	msr		cpsr_c, #0xc0|0x13			/* SVC ���� Ŀ�� ����								*/

	bl			main									/* main() ȣ�� 											*/
	b			_ram_entry

/*
����������������������������������������������������������������������������������������������
��				 										 [ SOFT Context Switching ]													   ��
����������������������������������������������������������������������������������������������
*/

kernel_soft_CS:									/* ����Ʈ���� ������ȯ 								*/

	stmfd	sp!, {lr}								/* �ǵ��ư� PC�� ���ÿ� PUSH					*/
	stmfd	sp!, {r0 - r12, lr}					/* r0~r12, LR�� ���ÿ� PUSH						*/
	mrs		r0, cpsr
	stmfd	sp!, {r0}								/* CPSR�� ���ÿ� PUSH								*/

	ldr			r0, =curPCB
	ldr			r0, [r0]
	str			sp, [r0]								/* ���� PCB�� ����Ű�� �����Ϳ� sp ����	*/

	bl			change_Prio						/* �켱������ �����Ѵ�								*/
	bl			change_PCB						/* PCB�� �����Ѵ� 									*/

	ldr			r0, =highPCB
	ldr			r0, [r0]
	ldr			sp, [r0]								/* ���� PCB�� ����Ű�� �����Ϳ��� SP�ε�	*/

	ldmfd 	sp!, {r0}								/* CPSR�� �������κ��� POP						*/
	msr 		cpsr_cxsf, #0x00000013	/* SVC���� ��ȯ 		 							*/
	ldmfd	sp!, {r0 - r12, lr, pc}			/* r0~r12, LR, PC�� ���ÿ��� POP				*/

/*
����������������������������������������������������������������������������������������������
��				 										 [ HARD Context Switching ]													   ��
����������������������������������������������������������������������������������������������
*/

kernel_hard_CS:									/* �ϵ���� ������ȯ 								*/

	add		sp,sp,#20							/* SVS��� SP�� �����Ѵ� 							*/

	ldr			r0,=curPCB
	ldr			r0, [r0]
	str			sp, [r0]								/* ���� PCB�� ����Ű�� �����Ϳ� sp ����	*/

	bl			change_Prio						/* �켱������ �����Ѵ�								*/
	bl			change_PCB						/* PCB�� �����Ѵ� 									*/

	ldr			r0, =highPCB
	ldr			r0, [r0]
	ldr			sp, [r0]								/* ���� PCB�� ����Ű�� �����Ϳ��� SP�ε�	*/

	ldmfd 	sp!, {r0}								/* CPSR�� �������κ��� POP						*/
	msr		cpsr_cxsf,#0x00000013		/* SVC���� ��ȯ 		 							*/
	ldmfd	sp!, {r0 - r12, lr, pc}			/* r0~r12, LR, PC�� ���ÿ��� POP				*/

/*
����������������������������������������������������������������������������������������������
��														 [ kernel tick handler]															   ��
����������������������������������������������������������������������������������������������
*/

kernel_tick:										/* Ÿ�� ƽ �ڵ鷯 										*/

	stmfd	sp!, {r0 - r3}						/* r0~r3�� ���ÿ� PUSH								*/

	mov		r2, sp
	add		sp, sp, #16						/* IRQ������ ����� �޸� 4���� ��� 		*/
	sub		r3, lr, #4							/* IRQ���κ��� ������ �ּ� r3�� ���� 		*/
	

	msr		cpsr_cxsf, #0x00000093	/* SVC���� ��ȯ 									*/
	stmfd	sp!, {r3}								/* �ǵ��ư� PC�� ���ÿ� PUSH					*/
	stmfd	sp!, {r4 - r12, lr}					/* r0~r12, LR�� ���ÿ� PUSH						*/
	mov		r4, r2
	ldmfd	r4!, {r0 - r3}						/* IRQ�������κ��� r0~r3 POP	 				*/
	stmfd	sp!, {r0 - r3}						/* SVC���ÿ� r0~r3 PUSH							*/

	mrs		r0, cpsr
	stmfd	sp!, {r0}								/* CPSR�� ���ÿ� PUSH								*/	

	bl			irqHandler							/* timer �ʱ�ȭ 											*/	
	bl			tick									/* PCB -> time �� 1������ 							*/
	bl			ISR									/* kernel_hard_CS ȣ���Լ� 						*/

	ldmfd	sp!, {r0 - r3}
	stmfd	sp!, {r0 - r3}

	ldmfd 	sp!, {r0}								/* CPSR�� �������κ��� POP						*/
	msr		cpsr_cxsf, #0x00000013	/* SVC���� ��ȯ 		 							*/
	ldmfd	sp!, {r0 - r12, lr, pc}			/* r0~r12, LR, PC�� ���ÿ��� POP				*/

/*
����������������������������������������������������������������������������������������������
��				 												 [ kernel_entry ]															   ��
����������������������������������������������������������������������������������������������
*/

kernel_entry:										/* Ŀ�� ���� �ڵ� 						 				*/

	ldr			r0, =highPCB
	ldr			r0, [r0]
	ldr			sp, [r0]								/* ���� PCB�� ����Ű�� �����Ϳ��� SP�ε�	*/

	ldmfd	sp!, {r0}
	msr		cpsr_cxsf, r0						/* CPSR �ʱ�ȭ = SVC ��� 						*/

	bl			os_timer_init						/* Ÿ�̸� �ʱ�ȭ 										*/
	bl			os_timer_start					/* Ÿ�̸� ���� 											*/

	ldmfd	sp!, {r0 - r12, lr, pc}

/*
����������������������������������������������������������������������������������������������
��				 											 [ Enable Interrupt ]															   ��
����������������������������������������������������������������������������������������������
*/

kernel_enable_int:								/* ���ͷ�Ʈ Ȱ��ȭ �ڵ� 							*/

	mrs		r1, cpsr
	bic		r1, r1, #0x80						/* BIC �������� ���ͷ�Ʈ Ȱ�� 					*/
	msr		cpsr, r1
	mov		pc, lr

/*
����������������������������������������������������������������������������������������������
��				 											 [ Disable Interrupt ]														   ��
����������������������������������������������������������������������������������������������
*/

kernel_disable_int:								/* ���ͷ�Ʈ ��Ȱ��ȭ �ڵ� 							*/

	mrs		r1, cpsr
	orr 		r1, r1, #0x80						/* ORR �������� ���ͷ�Ʈ ��Ȱ�� 				*/
	msr 		cpsr, r1
	mov 		pc, lr
