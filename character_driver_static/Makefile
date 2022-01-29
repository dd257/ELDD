	obj-m += main.o

	DIR = /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(DIR) M=$(PWD) modules
	gcc -o app app.c

install:
	$(MAKE) -C $(DIR) M=$(PWD) modules_install

prepare:
	$(MAKE) -C $(DIR) M=$(PWD) modules_prepare

clean:
	$(MAKE) -C $(DIR) M=$(PWD) clean