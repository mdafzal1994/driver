obj-m:=add.o average.o
KERNELDIR =/usr/src/linux-headers-$(shell uname -r)/
#KERNELDIR = /usr/src/linux-headers-5.4.0-48-generic/
PWD := $(shell pwd)

default :
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean  :
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean

install :
	$(MAKE) -C $(KERNELDIR) M=$(PWD) install
	depmod -a

