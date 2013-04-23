###############################################################################
#
# Makefile for drivers
#
###############################################################################



ifneq ($(KERNELRELEASE),)
	obj-m := ${MODULE}.o

else

	KERNELDIR ?= ../linux/
	PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

endif

.PHONY: clean
clean:
	rm -Rf *.ko *.o *.mod.c Module.symvers modules.order