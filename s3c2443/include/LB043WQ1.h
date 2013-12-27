/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃			  														  lapetOS			   													   ┃
┃				 						 [ General Purpose Kernel for Embedded System ]									   ┃
┃			  																   																	   ┃
┃			  							  					SangMyung University									   					   ┃
┃			  							  				  Computer Science Major												       ┃
┃			  																				   													   ┃
┃					  					  Made By: Yoo Sang-Gi / Park Il-Kwon, 2011-2012							  	   ┃
┃			  											 	 File Name: LB043WQ1.h												   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

#ifndef __LB043WQ1_H__
#define __LB043WQ1_H__

#define LB043WQ1_VBPD          (12)
#define LB043WQ1_VFPD          (4)
#define LB043WQ1_VSPW          (10)
#define LB043WQ1_HBPD          (45)
#define LB043WQ1_HFPD          (2)
#define LB043WQ1_HSPW          (41)
#define LB043WQ1_XSIZE         (480)
#define LB043WQ1_YSIZE         (272)
#define LB043WQ1_FRAME_RATE    (60)

void LB043WQ1_Init(void);

#endif /* __LB043WQ1_H__ */
