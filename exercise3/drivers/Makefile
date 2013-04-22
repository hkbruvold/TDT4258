###############################################################################
#
# Makefile for drivers
#
###############################################################################

MODULE=button.c

ifneq ($(KERNELRELEASE),)
    obj-m := ${MODULE}.o

else

    KERNELDIR ?= /lib/modules/$(shell uname -r)/build
    PWD := $(shell pwd)

default:
    $(MAKE) -C $(KERNELDIR) M=$(PWD) modules

endif