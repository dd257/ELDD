#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

static int add(int a, int b)
{
    return a+b;
}

EXPORT_SYMBOL(add);

static int __init insert(void)
{
    printk("Inserting Addition Module\n");
    return 0;
}

static void __exit remove(void)
{
    printk("Removing module\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RAHUL");
MODULE_DESCRIPTION("Program to export symbols");

module_init(insert);
module_exit(remove);