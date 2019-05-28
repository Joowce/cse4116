obj-m := interrupt.o device.o timer.o stopwatch_controller.o

KDIR := /work/achroimx_kernel/
PWD := $(shell pwd)

default :
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules 

clean : 
	rm -f *.ko
	rm -f *.o
	rm -f *.mod.*
	rm -f *.cmd
	rm -f *.symvers
	rm -f *.order
