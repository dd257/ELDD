#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

static int num[2]={12,14};
int c=2;

module_param_array(num,int,&c,S_IRUGO);

static int __init insert(void)
{
    int i=0;
    printk("Inserting Module\n");
    for(i=0;i<c;i++)
        printk("%d\n",i+1);
    return 0;
}

static void __exit delete(void)
{
    printk("Exiting Module\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rahul");
MODULE_DESCRIPTION("Assigning Array in Module parameters");

module_init(insert);
module_exit(delete);