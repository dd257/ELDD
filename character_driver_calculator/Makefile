	obj-m += main.o

	DIR = /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(DIR) M=$(PWD) modules
	gcc -o add add.c
	gcc -o sub sub.c
	gcc -o mul mul.c
	gcc -o div div.c

install:
	$(MAKE) -C $(DIR) M=$(PWD) modules_install
	depmod -a

prepare:
	$(MAKE) -C $(DIR) M=$(PWD) modules_prepare

clean:
	$(MAKE) -C $(DIR) M=$(PWD) clean

dev:
	mknod  /dev/add_dev c 240 0
	mknod  /dev/sub_dev c 240 1
	mknod  /dev/mul_dev c 240 2
	mknod  /dev/div_dev c 240 3