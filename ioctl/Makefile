	obj-m += main.o

	DIR = /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(DIR) M=$(PWD) modules
	gcc -o config config.c

install:
	$(MAKE) -C $(DIR) M=$(PWD) modules_install

prepare:
	$(MAKE) -C $(DIR) M=$(PWD) modules_prepare

clean:
	$(MAKE) -C $(DIR) M=$(PWD) clean

dev:
	mknod /dev/myioctl c 240 0