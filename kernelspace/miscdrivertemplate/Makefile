# File: Makefile
#
# Makefile for misc driver template.
#
# kernel 2.6
# Test on device: AC49x

PWD_DIR = $(shell pwd)
KERNEL_PATH := $(shell pwd)/../../kernel/linux494and495/linux-2.6.10_dev-malta-mips2_fp_len/
EXTRA_CFLAGS += -I$(KERNEL_PATH)/include/asm-mips/mach-avalanche/generic/
EXTRA_CFLAGS += -I$(KERNEL_PATH)/include/asm-mips/mach-avalanche/titan/
EXTRA_CFLAGS += -I$(KERNEL_PATH)/include/asm-mips/mach-generic/

DRIVER_NAME := "miscdrv_template"

obj-m += $(DRIVER_NAME)_drv.o
$(DRIVER_NAME)_drv-objs := $(DRIVER_NAME).o

$(DRIVER_NAME):
	export PATH=/opt/codefidence/bin:$(PATH); make -C $(KERNEL_PATH) M=$(PWD_DIR) modules

clean:
	rm -rf *.o *.mod.c *.ko *.cmd *.ko.cmd .*.o.cmd .*.ko.cmd .tmp_versions
