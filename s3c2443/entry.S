/*
¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶
¦­			  														  lapetOS			   													   ¦­
¦­				 						 [ General Purpose Kernel for Embedded System ]									   ¦­
¦­			  																   																	   ¦­
¦­			  							  					SangMyung University									   					   ¦­
¦­			  							  				  Computer Science Major												       ¦­
¦­			  																				   													   ¦­
¦­					  					  Made by: Yoo Sang-Gi / Park Il-Kwon, 2011-2012							  	   ¦­
¦­			  											 	   File Name: entry.S		 												   ¦­
¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶
*/

#define svc_stack	0x30300000				/* SVC ¸ðµå ½ºÅÃ ¹øÁö							*/
#define irq_stack	0x30380000				/* IRQ ¸ðµå ½ºÅÃ ¹øÁö								*/

.global	_ram_entry
.global	kernel_init
.global	kernel_soft_CS
.global	kernel_hard_CS
.global	kernel_tick
.global	kernel_entry
.global	kernel_enable_int
.global	kernel_disable_int

/*
¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶
¦­				 													 [ Ram Entry ]															   ¦­
¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶
*/

_ram_entry:											/* ·¥ ¿£Æ®¸®: ºÎÆ®·Î´õ¿¡¼­ ÁÖ¼Ò¸¦ ÂüÁ¶	*/

	b		kernel_init
	b		_ram_entry
	b		kernel_soft_CS
	b		kernel_tick
	b		kernel_hard_CS
	b		kernel_entry
	b		kernel_enable_int
	b		kernel_disable_int

/*
¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶
¦­				 												 [ kernel Initialize ]														   ¦­
¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶
*/

kernel_init:

	msr		cpsr_c, #0x40|0x12			/* IRQ ¸ðµå º¯°æ ÈÄ stack pointer ÃÊ±âÈ­		*/
	ldr			sp, =irq_stack
	msr		cpsr_c, #0x40|0x13			/* SVC ¸ðµå º¯°æ ÈÄ stack pointer ÃÊ±âÈ­		*/
	ldr			sp, =svc_stack
	msr		cpsr_c, #0xc0|0x13			/* SVC ¸ðµå·Î Ä¿³Î ÁøÀÔ								*/

	bl			main									/* main() È£Ãâ 											*/
	b			_ram_entry

/*
¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶
¦­				 										 [ SOFT Context Switching ]													   ¦­
¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶
*/

kernel_soft_CS:									/* ¼ÒÇÁÆ®¿þ¾î ¹®¸ÆÀüÈ¯ 								*/

	stmfd	sp!, {lr}								/* µÇµ¹¾Æ°¥ PC°ª ½ºÅÃ¿¡ PUSH					*/
	stmfd	sp!, {r0 - r12, lr}					/* r0~r12, LR°ª ½ºÅÃ¿¡ PUSH						*/
	mrs		r0, cpsr
	stmfd	sp!, {r0}								/* CPSR°ª ½ºÅÃ¿¡ PUSH								*/

	ldr			r0, =curPCB
	ldr			r0, [r0]
	str			sp, [r0]								/* ÇöÀç PCB°¡ °¡¸®Å°´Â Æ÷ÀÎÅÍ¿¡ sp ÀúÀå	*/

	bl			change_Prio						/* ¿ì¼±¼øÀ§¸¦ º¯°æÇÑ´Ù								*/
	bl			change_PCB						/* PCB¸¦ º¯°æÇÑ´Ù 									*/

	ldr			r0, =highPCB
	ldr			r0, [r0]
	ldr			sp, [r0]								/* ´ÙÀ½ PCB°¡ °¡¸®Å°´Â Æ÷ÀÎÅÍ¿¡¼­ SP·Îµå	*/

	ldmfd 	sp!, {r0}								/* CPSR°ª ½ºÅÃÀ¸·ÎºÎÅÍ POP						*/
	msr 		cpsr_cxsf, #0x00000013	/* SVC¸ðµå·Î ÀüÈ¯ 		 							*/
	ldmfd	sp!, {r0 - r12, lr, pc}			/* r0~r12, LR, PC°ª ½ºÅÃ¿¡¼­ POP				*/

/*
¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶
¦­				 										 [ HARD Context Switching ]													   ¦­
¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶
*/

kernel_hard_CS:									/* ÇÏµå¿þ¾î ¹®¸ÆÀüÈ¯ 								*/

	add		sp,sp,#20							/* SVS¸ðµå SP¸¦ º¹±¸ÇÑ´Ù 							*/

	ldr			r0,=curPCB
	ldr			r0, [r0]
	str			sp, [r0]								/* ÇöÀç PCB°¡ °¡¸®Å°´Â Æ÷ÀÎÅÍ¿¡ sp ÀúÀå	*/

	bl			change_Prio						/* ¿ì¼±¼øÀ§¸¦ º¯°æÇÑ´Ù								*/
	bl			change_PCB						/* PCB¸¦ º¯°æÇÑ´Ù 									*/

	ldr			r0, =highPCB
	ldr			r0, [r0]
	ldr			sp, [r0]								/* ´ÙÀ½ PCB°¡ °¡¸®Å°´Â Æ÷ÀÎÅÍ¿¡¼­ SP·Îµå	*/

	ldmfd 	sp!, {r0}								/* CPSR°ª ½ºÅÃÀ¸·ÎºÎÅÍ POP						*/
	msr		cpsr_cxsf,#0x00000013		/* SVC¸ðµå·Î ÀüÈ¯ 		 							*/
	ldmfd	sp!, {r0 - r12, lr, pc}			/* r0~r12, LR, PC°ª ½ºÅÃ¿¡¼­ POP				*/

/*
¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶
¦­														 [ kernel tick handler]															   ¦­
¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶
*/

kernel_tick:										/* Å¸ÀÓ Æ½ ÇÚµé·¯ 										*/

	stmfd	sp!, {r0 - r3}						/* r0~r3°ª ½ºÅÃ¿¡ PUSH								*/

	mov		r2, sp
	add		sp, sp, #16						/* IRQ½ºÅÃÀÌ »ç¿ëÇÒ ¸Þ¸ð¸® 4°ø°£ ºñ¿ò 		*/
	sub		r3, lr, #4							/* IRQ¸ðµå·ÎºÎÅÍ º¹±ÍÇÒ ÁÖ¼Ò r3¿¡ ÀúÀå 		*/
	

	msr		cpsr_cxsf, #0x00000093	/* SVC¸ðµå·Î ÀüÈ¯ 									*/
	stmfd	sp!, {r3}								/* µÇµ¹¾Æ°¥ PC°ª ½ºÅÃ¿¡ PUSH					*/
	stmfd	sp!, {r4 - r12, lr}					/* r0~r12, LR°ª ½ºÅÃ¿¡ PUSH						*/
	mov		r4, r2
	ldmfd	r4!, {r0 - r3}						/* IRQ½ºÅÃÀ¸·ÎºÎÅÍ r0~r3 POP	 				*/
	stmfd	sp!, {r0 - r3}						/* SVC½ºÅÃ¿¡ r0~r3 PUSH							*/

	mrs		r0, cpsr
	stmfd	sp!, {r0}								/* CPSR°ª ½ºÅÃ¿¡ PUSH								*/	

	bl			irqHandler							/* timer ÃÊ±âÈ­ 											*/	
	bl			tick									/* PCB -> time °ª 1¾¿°¨¼Ò 							*/
	bl			ISR									/* kernel_hard_CS È£ÃâÇÔ¼ö 						*/

	ldmfd	sp!, {r0 - r3}
	stmfd	sp!, {r0 - r3}

	ldmfd 	sp!, {r0}								/* CPSR°ª ½ºÅÃÀ¸·ÎºÎÅÍ POP						*/
	msr		cpsr_cxsf, #0x00000013	/* SVC¸ðµå·Î ÀüÈ¯ 		 							*/
	ldmfd	sp!, {r0 - r12, lr, pc}			/* r0~r12, LR, PC°ª ½ºÅÃ¿¡¼­ POP				*/

/*
¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶
¦­				 												 [ kernel_entry ]															   ¦­
¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶
*/

kernel_entry:										/* Ä¿³Î ºÎÆÃ ÄÚµå 						 				*/

	ldr			r0, =highPCB
	ldr			r0, [r0]
	ldr			sp, [r0]								/* ´ÙÀ½ PCB°¡ °¡¸®Å°´Â Æ÷ÀÎÅÍ¿¡¼­ SP·Îµå	*/

	ldmfd	sp!, {r0}
	msr		cpsr_cxsf, r0						/* CPSR ÃÊ±âÈ­ = SVC ¸ðµå 						*/

	bl			os_timer_init						/* Å¸ÀÌ¸Ó ÃÊ±âÈ­ 										*/
	bl			os_timer_start					/* Å¸ÀÌ¸Ó ½ÃÀÛ 											*/

	ldmfd	sp!, {r0 - r12, lr, pc}

/*
¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶
¦­				 											 [ Enable Interrupt ]															   ¦­
¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶
*/

kernel_enable_int:								/* ÀÎÅÍ·´Æ® È°¼ºÈ­ ÄÚµå 							*/

	mrs		r1, cpsr
	bic		r1, r1, #0x80						/* BIC ¿¬»êÀ¸·Î ÀÎÅÍ·´Æ® È°¼º 					*/
	msr		cpsr, r1
	mov		pc, lr

/*
¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶
¦­				 											 [ Disable Interrupt ]														   ¦­
¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶
*/

kernel_disable_int:								/* ÀÎÅÍ·´Æ® ºñÈ°¼ºÈ­ ÄÚµå 							*/

	mrs		r1, cpsr
	orr 		r1, r1, #0x80						/* ORR ¿¬»êÀ¸·Î ÀÎÅÍ·´Æ® ºñÈ°¼º 				*/
	msr 		cpsr, r1
	mov 		pc, lr

