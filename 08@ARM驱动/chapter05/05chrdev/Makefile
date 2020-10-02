CROSS_COMPILE=arm-linux-
CC=$(CROSS_COMPILE)gcc

obj-m += chrdev_led.o

all:
	make -C /home/devin/Documents/ARM/kernel/linux-3.0.8/ SUBDIRS=$(PWD) ARCH=arm modules

clean:
	make -C /home/devin/Documents/ARM/kernel/linux-3.0.8/ SUBDIRS=$(PWD) clean
