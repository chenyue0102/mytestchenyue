KVERS := $(shell uname -r)
CURDIR := $(shell pwd)
CONFIG_MODULE_SIG=n
obj-m := test.o
KERNEL_DIR=/lib/modules/$(KVERS)/build
build:kernel_modules

kernel_modules:
	$(MAKE) -C $(KERNEL_DIR) M=$(CURDIR) modules
	
clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(CURDIR) clean