#include<linux/init.h>
#include<linux/module.h>

static int __init hello_init(void)
{
	printk("Hello\n");
	return 0;
}

static void __exit hello_exit(void)
{
	printk("Bye\n");
}

module_init(hello_init);
module_exit(hello_exit);
	
MODULE_LICENSE("GPL");
MODULE_AUTHOR("RAHUL");
MODULE_DESCRIPTION("hello.c");
