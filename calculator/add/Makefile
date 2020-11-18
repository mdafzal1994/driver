obj-m:=add.o

KERNELDIR=/usr/src/linux-headers-$(shell uname -r)
PDW=$(shell pwd)


default:
	make -C $(KERNELDIR) M=$(PWD)
