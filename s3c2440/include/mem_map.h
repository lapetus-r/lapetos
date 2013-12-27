/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃			  														  lapetOS			   													   ┃
┃				 						 [ General Purpose Kernel for Embedded System ]									   ┃
┃			  																   																	   ┃
┃			  							  					SangMyung University									   					   ┃
┃			  							  				  Computer Science Major												       ┃
┃			  																				   													   ┃
┃					  					  Made By: Yoo Sang-Gi / Park Il-Kwon, 2011-2012							  	   ┃
┃			  											 	 File Name: mem_map.h	 												   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

#ifndef _MEM_MAP_HEADER_
#define _MEM_MAP_HEADER_

#define LINUX_MACH_TYPE                 784

#define DEFAULT_nCS_NAND_BASE           (S3C2440_CS0_PHYS) 
#define DEFAULT_nCS_AX88796B_BASE		(S3C2440_CS1_PHYS)	// EtherNet AX88796B
#define DEFAULT_nCS_CS8900_BASE         (S3C2440_CS1_PHYS)	// EtherNet CS8900
#define BANK0_START                     (S3C2440_CS6_PHYS)	// 뱅크0 시작 위치
#define BANK0_SIZE                      (64*1024*1024)      // 뱅크0 크기 마지막주소는 0x33ffffff

#define DEFAULT_NAND_BOOT				0x00000000          // 난드 부트 시작 어드레스 
#define DEFAULT_BOOT_SIZE              	(128*1024)		    // 부트영역의 크기

#define DEFAULT_RAM_KERNEL_START        0x30008000          // 램에서 커널     시작 어드레스 
#define DEFAULT_RAM_RAMDISK_START       0x30800000          // 램에서 램디스크 시작 어드레스 
#define DEFAULT_RAM_BOOT_START          0x30F00000          // 램에서 부트     시작 어드레스 
#define DEFAULT_RAM_WORK_START          0x31000000          // 일반적인 부트 로더 작업 영역 
#define DEFAULT_RAM_BOOTLOGO_START		0x32000000			// 램에서 부트로고 시작 어드레스

#define DEFAULT_RAM_KERNEL_ZERO_PAGE    S3C2440_CS6_PHYS	// 부트로더에서 커널로 전달하는 영역 시작 어드레스 

#endif //_MEM_MAP_HEADER_

