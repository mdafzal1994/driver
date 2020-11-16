obj-m:=demo.o

kerneldriv=/usr/src/linux-headers-$(shell uname -r)/
PWD=$(shell pwd)

default:
	make -C $(kerneldriv) M=$(PWD)


