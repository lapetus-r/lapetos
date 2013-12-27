/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃			  														  lapetOS			   													   ┃
┃				 						 [ General Purpose Kernel for Embedded System ]									   ┃
┃			  																   																	   ┃
┃			  							  					SangMyung University									   					   ┃
┃			  							  				  Computer Science Major												       ┃
┃			  																				   													   ┃
┃					  					  Made by: Yoo Sang-Gi / Park Il-Kwon, 2011-2012							  	   ┃
┃			  											 	   File Name: time.c		 												   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/
#include <time.h>
#include <s3c2440.h>
// 설명 : 워치독 설정

void	SetWatchdog( int msec )
{
		WTDAT  = (TICKS_PER_SECOND*msec)/1000;
		WTCNT  = (TICKS_PER_SECOND*msec)/1000;
}

// 설명 : 타이머를 초기화 한다. 

void TimerInit(void)
{
		//unsigned int startTime;
	
		TCFG0  = TCFG0_VALUE;	// Timer Configuration Register0
		TCFG1  = TCFG1_VALUE;	// Timer Configuration Register1
	
		// Timer0 Count Buffer 			
		TCNTB0 = 0xFFFF;
		TCMPB0 = 0x00;

		// Timer1 Count Buffer 			
		TCNTB1 = TICKS_PER_SECOND-1;
		TCMPB1 = TCNTB1/2;

		// Timer2 Count Buffer 			
		TCNTB2 = TICKS_PER_SECOND-1;
		TCMPB2 = TCNTB2/2;

		// Timer3 Count Buffer 			
    		TCNTB3 = TICKS_PER_SECOND-1;
		TCMPB3 = TCNTB3/2;

		// Timer4 Count Buffer 			
    		TCNTB4 = TICKS_PER_SECOND-1;
		TCON   = 0x00000000;

		// Timer-0를 초기화 한다.
		TCON  = (TCON_TM0_UPDATE_MANUAL);	// Manual update
	        TCON  = (TCON & 0xFFFFFFF0) | (TCON_TM0_ONE_SHOT | TCON_TM0_STOP);

		// WATCHDOG Timer를 초기화 한다.		
		WTCON = WTCON_VALUE;    
}

// 설명 : 부트로더 환경 설정을 위한 타이머 초기화

void	TimerConfigTime(void)
{  
		// Timer-1를 초기화 한다.
		TCON  = (TCON_TM1_UPDATE_MANUAL);
        TCON  = (TCON & 0xFFFFF0FF) | (TCON_TM1_AUTO_RELOAD | TCON_TM1_START);
}

// 설명 : 타이머의 값을 얻어 온다. 

unsigned int  TimerGetTime(void)
{
		return ( ( unsigned int ) ( 65536 - ( TCNTO1 & 0xffff ) ) );
}

// 설명 : 밀리 세컨드 동안 지연을 갇는다.

void 	msleep(unsigned int msec)
{
	FreeTimer( 0 );
        ReloadTimer( 0, msec );
        while( 0 == TimeOverflow(0) );
        FreeTimer( 0 );
}

// 설명 : 다운카운터의 값을 다시 불러온다.

void    ReloadTimer( unsigned char bTimer, unsigned int msec )
{
		// 타이머 오버플로우가 발생할 틱
        switch( bTimer )
        {
        case 0 :
        	TCNTB0  = (TICKS_PER_SECOND*msec)/1000;
			TCON    = (TCON|TCON_TM0_UPDATE_MANUAL);
//			X	    = ( 1  << 1);
	        TCON    = (TCON & 0xFFFFFFF0) | (TCON_TM0_ONE_SHOT | TCON_TM0_START);
//		X	    = ( X       & 0xFFFFFFF0) | (0 << 3 |  1 << 0);
        	break;
        case 1 : 
        	TCNTB1 	= (TICKS_PER_SECOND*msec)/1000;
			TCON    = (TCON_TM1_UPDATE_MANUAL);
	        TCON    = (TCON & 0xFFFFF0FF) | (TCON_TM1_ONE_SHOT | TCON_TM1_START);
        	break;
        case 2 : 
        	TCNTB2 	= (TICKS_PER_SECOND*msec)/1000;
			TCON    = (TCON_TM2_UPDATE_MANUAL);
	        TCON    = (TCON & 0xFFFF0FFF) | (TCON_TM2_ONE_SHOT | TCON_TM2_START);
        	break;
        case 3 : 
        	TCNTB3 	= (TICKS_PER_SECOND*msec)/1000;
			TCON    = (TCON_TM3_UPDATE_MANUAL);
	        TCON    = (TCON & 0xFFF0FFFF) | (TCON_TM3_ONE_SHOT | TCON_TM3_START);
        	break;
        case 4 : 
        	TCNTB4 	= (TICKS_PER_SECOND*msec)/1000;				
			TCON    = (TCON_TM4_UPDATE_MANUAL);
	        TCON    = (TCON & 0xFF0FFFFF) | (TCON_TM4_ONE_SHOT | TCON_TM4_START);
        	break;
		}

}

// 설명 : 오버플로우 체크

int     TimeOverflow( unsigned char bTimer )
{
        unsigned long reg;
        
		reg = SRCPND;
        
        switch( bTimer )
        {
        case 0 :	
        	reg &= TIMER0;
        	break;
        case 1 : 
        	reg &= TIMER1;
        	break;
        case 2 : 
        	reg &= TIMER2;
        	break;
        case 3 : 
        	reg &= TIMER3;
        	break;
        case 4 : 
        	reg &= TIMER4;
        	break;
        }
		return reg;
}

// 설명 : 타이머를 정지시키고 타이머 오버플로우 발생 비트를 클리어시킨다.

void    FreeTimer( unsigned char bTimer )
{
        // 타이머 오버플로우가 클리어
        switch( bTimer )
        {
        case 0 :
	        TCON    = (TCON & 0xFFFFFFF0) | (TCON_TM0_ONE_SHOT | TCON_TM0_STOP);
			SRCPND |= TIMER0;
        	break;
        case 1 : 
	        TCON    = (TCON & 0xFFFFF0FF) | (TCON_TM1_ONE_SHOT | TCON_TM1_STOP);
			SRCPND |= TIMER1;
        	break;
        case 2 : 
	        TCON    = (TCON & 0xFFFF0FFF) | (TCON_TM2_ONE_SHOT | TCON_TM2_STOP);
			SRCPND |= TIMER2;
        	break;
        case 3 : 
	        TCON    = (TCON & 0xFFF0FFFF) | (TCON_TM3_ONE_SHOT | TCON_TM3_STOP);
			SRCPND |= TIMER3;
        	break;
        case 4 : 
	        TCON    = (TCON & 0xFF0FFFFF) | (TCON_TM4_ONE_SHOT | TCON_TM4_STOP);
			SRCPND |= TIMER4;
        	break;
        }
}

