cmd_/home/rahul/Linux_Device_Drivers/hello/hello.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000  --build-id  -T ./scripts/module-common.lds -o /home/rahul/Linux_Device_Drivers/hello/hello.ko /home/rahul/Linux_Device_Drivers/hello/hello.o /home/rahul/Linux_Device_Drivers/hello/hello.mod.o;  true