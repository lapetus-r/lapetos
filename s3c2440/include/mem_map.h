#ifndef _MEM_MAP_HEADER_
#define _MEM_MAP_HEADER_

#define LINUX_MACH_TYPE                 784

#define DEFAULT_nCS_NAND_BASE           (S3C2440_CS0_PHYS) 
#define DEFAULT_nCS_AX88796B_BASE		(S3C2440_CS1_PHYS)	// EtherNet AX88796B
#define DEFAULT_nCS_CS8900_BASE         (S3C2440_CS1_PHYS)	// EtherNet CS8900
#define BANK0_START                     (S3C2440_CS6_PHYS)	// ��ũ0 ���� ��ġ
#define BANK0_SIZE                      (64*1024*1024)      // ��ũ0 ũ�� �������ּҴ� 0x33ffffff

#define DEFAULT_NAND_BOOT				0x00000000          // ���� ��Ʈ ���� ��巹�� 
#define DEFAULT_BOOT_SIZE              	(128*1024)		    // ��Ʈ������ ũ��

#define DEFAULT_RAM_KERNEL_START        0x30008000          // ������ Ŀ��     ���� ��巹�� 
#define DEFAULT_RAM_RAMDISK_START       0x30800000          // ������ ����ũ ���� ��巹�� 
#define DEFAULT_RAM_BOOT_START          0x30F00000          // ������ ��Ʈ     ���� ��巹�� 
#define DEFAULT_RAM_WORK_START          0x31000000          // �Ϲ����� ��Ʈ �δ� �۾� ���� 
#define DEFAULT_RAM_BOOTLOGO_START		0x32000000			// ������ ��Ʈ�ΰ� ���� ��巹��

#define DEFAULT_RAM_KERNEL_ZERO_PAGE    S3C2440_CS6_PHYS	// ��Ʈ�δ����� Ŀ�η� �����ϴ� ���� ���� ��巹�� 

#endif //_MEM_MAP_HEADER_
