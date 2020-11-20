obj-m:=cirl_buff.o

kerneldir=/usr/src/linux-headers-$(shell uname -r)/
PWD=$(shell pwd)


default:
	make -C $(kerneldir)  M=$(PWD)
