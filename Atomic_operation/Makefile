obj-m:=atomic_demo.o


kerneldir=/usr/src/linux-headers-$(shell uname -r)/
PWD=$(shell pwd)


default:
	make -C $(kerneldir)  M=$(PWD)

clean  :
	$(MAKE) -C $(kerneldir) M=$(PWD) clean
