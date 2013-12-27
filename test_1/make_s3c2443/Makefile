#
#━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━#
#			  														  lapetOS			   													  #
#				 						 [ General Purpose Kernel for Embedded System ]									  #
#			  																   																	  #
#			  							  					SangMyung University									   					  #
#			  							  				  Computer Science Major												      #
#			  																				   													  #
#					  					  Made By: Yoo Sang-Gi / Park il-kwon, 2011-2012							  	  #
#			  											 	 File Name: Makefile	 													  #
#━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━#
#

CC = arm-linux-gcc
LD = arm-linux-ld
OC = arm-linux-objcopy

CFLAGS = -nostdinc -I. -I ../../s3c2443/include
CFLAGS += -Wall -Wstrict-prototypes -Wno-trigraphs -O2
CFLAGS += -fno-strict-aliasing -fno-common -pipe
CFLAGS += -mcpu=arm920t -msoft-float -fno-builtin

LDFLAGS = -L /lab/toolchain/arm-linux-gcc-3.3.2/lib/gcc-lib/arm-linux/3.3.2 -lgcc
LDFLAGS += -static -nostdlib -nostartfiles -nodefaultlibs -p -X -T ../../s3c2443/main-ld-script 
OCFLAGS = -O binary -R .note -R .comment -S

CFILES = ../test_1.c
HFILES = ../../s3c2443/include/include.h ../../src/include/kernel.h

all: $(CFILES) $(HFILES)
	$(CC) -c $(CFLAGS) -o ../../s3c2443/entry.o ../../s3c2443/entry.S
	$(CC) -c $(CFLAGS) -o ../../s3c2443/uart.o ../../s3c2443/uart.c
	$(CC) -c $(CFLAGS) -o ../../s3c2443/key.o ../../s3c2443/key.c
	$(CC) -c $(CFLAGS) -o ../../s3c2443/system.o ../../s3c2443/system.c
	$(CC) -c $(CFLAGS) -o ../../s3c2443/serial.o ../../s3c2443/serial.c
	$(CC) -c $(CFLAGS) -o ../../s3c2443/string.o ../../s3c2443/string.c
	$(CC) -c $(CFLAGS) -o ../../s3c2443/vsprintf.o ../../s3c2443/vsprintf.c
	$(CC) -c $(CFLAGS) -o ../../s3c2443/handler.o ../../s3c2443/handler.c
	$(CC) -c $(CFLAGS) -o ../../s3c2443/lib1funcs.o ../../s3c2443/lib1funcs.S
	$(CC) -c $(CFLAGS) -o ../../s3c2443/TFTLCD.o ../../s3c2443/TFTLCD.c
	$(CC) -c $(CFLAGS) -o ../../s3c2443/TFTLCDLIB.o ../../s3c2443/TFTLCD_LIB.c
	$(CC) -c $(CFLAGS) -o ../../src/core.o ../../src/core.c
	$(CC) -c $(CFLAGS) -o ../../src/init.o ../../src/init.c
	$(CC) -c $(CFLAGS) -o ../../src/proc.o ../../src/proc.c
	$(CC) -c $(CFLAGS) -o ../../src/semaphore.o ../../src/semaphore.c
	$(CC) -c $(CFLAGS) -o ../test_1.o ../test_1.c
	$(LD) $(LDFLAGS) -o test_1_elf ../../s3c2443/entry.o ../../s3c2443/handler.o ../../s3c2443/lib1funcs.o ../../s3c2443/uart.o ../../s3c2443/key.o ../../s3c2443/system.o ../../s3c2443/TFTLCD.o ../../s3c2443/TFTLCDLIB.o ../../s3c2443/serial.o ../../s3c2443/string.o ../../s3c2443/vsprintf.o ../../src/core.o ../../src/init.o ../../src/proc.o ../../src/semaphore.o ../test_1.o 
	$(OC) $(OCFLAGS) test_1_elf test_1_img
	cp test_1_img /lab/tftpboot/uImage-m24
	rm -rf ../*.o ../../src/*.o ../../s3c2443/*.o
	rm -rf test_1_elf
	rm -rf test_1_img

clean:
	rm -rf ../*.o ../../src/*.o ../../s3c2443/*.o
	rm -rf test_1_elf
	rm -rf test_1_img

