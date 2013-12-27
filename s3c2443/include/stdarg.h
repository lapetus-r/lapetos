/*
朱收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收朱
早			  														  lapetOS			   													   早
早				 						 [ General Purpose Kernel for Embedded System ]									   早
早			  																   																	   早
早			  							  					SangMyung University									   					   早
早			  							  				  Computer Science Major												       早
早			  																				   													   早
早					  					  Made By: Yoo Sang-Gi / Park Il-Kwon, 2011-2012							  	   早
早			  											 	File Name: stdarg.h		 												   早
朱收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收朱
*/

#ifndef _STDARG_HEADER_
#define _STDARG_HEADER_

typedef char *va_list;

#  define va_start(ap, p)	(ap = (char *) (&(p)+1))
#  define va_arg(ap, type)	((type *) (ap += sizeof(type)))[-1]
#  define va_end(ap)		((void)0)

#endif // _STDARG_HEADER_

