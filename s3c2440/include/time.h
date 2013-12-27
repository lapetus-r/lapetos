/*
����������������������������������������������������������������������������������������������
��			  														  lapetOS			   													   ��
��				 						 [ General Purpose Kernel for Embedded System ]									   ��
��			  																   																	   ��
��			  							  					SangMyung University									   					   ��
��			  							  				  Computer Science Major												       ��
��			  																				   													   ��
��					  					  Made By: Yoo Sang-Gi / Park Il-Kwon, 2011-2012							  	   ��
��			  											 	 File Name: time.h				 											   ��
����������������������������������������������������������������������������������������������
*/

#ifndef _TIME_HEADER_
#define _TIME_HEADER_

#define TICKS_PER_SECOND	(PCLK/(255+1)/16)
			
void			SetWatchdog( int msec );
void			TimerInit(void);             	// Ÿ�̸� �ʱ�ȭ 
unsigned int	TimerGetTime(void);       		// 1/TICKS_PER_SECOND �� �ð� ���� ��ȯ�Ѵ�. 
void			TimerConfigTime(void);			// Mac Address ������ ���� Setup ��ɿ����� �ð� �ʱ�ȭ
void			msleep(unsigned int msec);   	// �и������� �����ð����� ��� �Ѵ�. 

extern void		ReloadTimer( unsigned char bTimer, unsigned int msec);
extern int		TimeOverflow( unsigned char bTimer );
extern void		FreeTimer( unsigned char bTimer );

#endif //_TIME_HEADER_

