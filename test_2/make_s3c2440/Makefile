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

CFLAGS    = -nostdinc -I. -I ../../s3c2440/include
CFLAGS   += -Wall -Wstrict-prototypes -Wno-trigraphs -O2
CFLAGS   += -fno-strict-aliasing -fno-common -pipe -mapcs-32 
CFLAGS   += -mcpu=xscale -mshort-load-bytes -msoft-float -fno-builtin

LDFLAGS   = -static -nostdlib -nostartfiles -nodefaultlibs -p -X -T ../../s3c2440/main-ld-script
                
OCFLAGS = -O binary -R .note -R .comment -S

CFILES = ../test_2.c
HFILES = ../../src/include/kernel.h ../../s3c2440/include/gpio.h ../../s3c2440/include/s3c2440.h ../../s3c2440/include/serial.h ../../s3c2440/include/stdarg.h ../../s3c2440/include/stdio.h ../../s3c2440/include/string.h ../../s3c2440/include/time.h ../../s3c2440/include/lcd.h ../../s3c2440/include/mem_map.h ../../s3c2440/include/palette.h

all: $(CFILES) $(HFILES)
	$(CC) -c $(CFLAGS) -o ../../s3c2440/entry.o ../../s3c2440/entry.S
	$(CC) -c $(CFLAGS) -o ../../s3c2440/gpio.o ../../s3c2440/gpio.c
	$(CC) -c $(CFLAGS) -o ../../s3c2440/time.o ../../s3c2440/time.c
	$(CC) -c $(CFLAGS) -o ../../s3c2440/vsprintf.o ../../s3c2440/vsprintf.c
	$(CC) -c $(CFLAGS) -o ../../s3c2440/printf.o ../../s3c2440/printf.c
	$(CC) -c $(CFLAGS) -o ../../s3c2440/string.o ../../s3c2440/string.c
	$(CC) -c $(CFLAGS) -o ../../s3c2440/serial.o ../../s3c2440/serial.c
	$(CC) -c $(CFLAGS) -o ../../s3c2440/handler.o ../../s3c2440/handler.c
	$(CC) -c $(CFLAGS) -o ../../s3c2440/lib1funcs.o ../../s3c2440/lib1funcs.S
	$(CC) -c $(CFLAGS) -o ../../s3c2440/boot_logo.o ../../s3c2440/boot_logo.c
	$(CC) -c $(CFLAGS) -o ../../src/core.o ../../src/core.c
	$(CC) -c $(CFLAGS) -o ../../src/init.o ../../src/init.c
	$(CC) -c $(CFLAGS) -o ../../src/proc.o ../../src/proc.c
	$(CC) -c $(CFLAGS) -o ../../src/semaphore.o ../../src/semaphore.c
	$(CC) -c $(CFLAGS) -o ../test_2.o ../test_2.c
	$(LD) $(LDFLAGS) -o lapetOS_elf  ../../s3c2440/entry.o ../../s3c2440/gpio.o ../../s3c2440/time.o ../../s3c2440/vsprintf.o ../../s3c2440/printf.o ../../s3c2440/string.o ../../s3c2440/serial.o ../../s3c2440/handler.o ../../s3c2440/lib1funcs.o ../../s3c2440/boot_logo.o ../../src/core.o ../../src/init.o ../../src/proc.o ../../src/semaphore.o ../test_2.o
	$(OC) $(OCFLAGS) lapetOS_elf lapetOS_img
	rm ../*.o ../../src/*.o ../../s3c2440/*.o

clean:
	rm lapetOS_elf
	rm lapetOS_img

