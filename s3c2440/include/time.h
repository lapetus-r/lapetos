/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃			  														  lapetOS			   													   ┃
┃				 						 [ General Purpose Kernel for Embedded System ]									   ┃
┃			  																   																	   ┃
┃			  							  					SangMyung University									   					   ┃
┃			  							  				  Computer Science Major												       ┃
┃			  																				   													   ┃
┃					  					  Made By: Yoo Sang-Gi / Park Il-Kwon, 2011-2012							  	   ┃
┃			  											 	 File Name: time.h				 											   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

#ifndef _TIME_HEADER_
#define _TIME_HEADER_

#define TICKS_PER_SECOND	(PCLK/(255+1)/16)
			
void			SetWatchdog( int msec );
void			TimerInit(void);             	// 타이머 초기화 
unsigned int	TimerGetTime(void);       		// 1/TICKS_PER_SECOND 의 시간 값을 반환한다. 
void			TimerConfigTime(void);			// Mac Address 설정을 위한 Setup 명령에서의 시간 초기화
void			msleep(unsigned int msec);   	// 밀리세컨드 단위시간동안 대기 한다. 

extern void		ReloadTimer( unsigned char bTimer, unsigned int msec);
extern int		TimeOverflow( unsigned char bTimer );
extern void		FreeTimer( unsigned char bTimer );

#endif //_TIME_HEADER_

