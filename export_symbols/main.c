#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include"add/add.h"
#include"avg/avg.h"

static int x=0,y=0;

module_param(x,int,S_IRUGO);
module_param(y,int,S_IRUGO);

static int __init insert(void)
{
    printk("Inserting Module\n");
    printk("Sum(%d,%d) = %d\n",x,y,add(x,y));
    printk("Average(%d,%d) = %d\n",x,y,avg(x,y));
    return 0;
}

static void __exit remove(void)
{
    printk("Removing Module\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RAHUL");
MODULE_DESCRIPTION("Importing symbols");

module_init(insert);
module_exit(remove);