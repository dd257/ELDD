#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>

static char* var="There";

module_param(var,charp,S_IRUGO);

static int __init greet_init(void)
{
    printk("Hello %s\n",var);
    return 0;
}

static void __exit greet_exit(void)
{
    printk("BYE %s\n",var);
}

module_init(greet_init);
module_exit(greet_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rahul");
MODULE_DESCRIPTION("Assigning Module parameters");
