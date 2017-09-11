# File: Makefile
#
# Makefile for misc driver template.
#
# kernel: linux-2.6.10
# Test on device: AC49x

PWD_DIR = $(shell pwd)
KERNEL_PATH := /home/napat/forth/nursecallIp/ipnursecall/linux/kernel/linux494and495/linux-2.6.10_dev-malta-mips2_fp_len/
EXTRA_CFLAGS += -I$(KERNEL_PATH)/include/asm-mips/mach-avalanche/generic/
EXTRA_CFLAGS += -I$(KERNEL_PATH)/include/asm-mips/mach-avalanche/titan/
EXTRA_CFLAGS += -I$(KERNEL_PATH)/include/asm-mips/mach-generic/

TOOLCHAIN_PATH := /opt/codefidence/bin

DRIVER_NAME := proc_read

obj-m += $(DRIVER_NAME).o

all: $(DRIVER_NAME)

$(DRIVER_NAME):
	export PATH=$(TOOLCHAIN_PATH):$(PATH); make -C $(KERNEL_PATH) M=$(PWD_DIR) modules

clean:
	rm -rf *.o *.mod.c *.ko *.cmd *.ko.cmd .*.o.cmd .*.ko.cmd .tmp_versions

