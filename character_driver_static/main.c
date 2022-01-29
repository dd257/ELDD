#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/uaccess.h>
#include<linux/fs.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/cdev.h>

int device_open(struct inode *,struct file *);
int device_release(struct inode *,struct file *);
ssize_t dev_read(struct file *,char __user *,size_t,loff_t *);
ssize_t device_write(struct file *,const char __user *,size_t,loff_t *);

struct file_operations fops=
{
    .owner=THIS_MODULE,
    .read=dev_read,    
    .write=device_write,
    .open=device_open,
    .release=device_release,
};

struct cdev *my_cdev;

int device_open(struct inode *inode,struct file *filp)
{
    printk("Open call");
    return 0;
}

int device_release(struct inode *inode,struct file *filp)
{
    printk("Release call");
    return 0;
}

ssize_t dev_read(struct file *filp,char __user *Ubuff,size_t count,loff_t *offp)
{
    char Kbuff[]="Kernel Buffer";
    //char Kbuff[80];
    int result;
    //ssize_t retval;

    //strcpy(Kbuff,Ubuff);

    result=copy_to_user(Ubuff,Kbuff,sizeof(Kbuff));

    if (result<0)
    {
        printk("Copy to User failed\n");
        return -1;
    }

    printk("Data read by User %s: %s\n",(result>0)?("Incomplete"):("Complete"),Ubuff);

    return count-result;
}

ssize_t device_write(struct file *filp,const char __user *Ubuff,size_t count,loff_t *offp)
{
    char Kbuff[80];
    int result;
    //ssize_t retval;

    //strcpy(Kbuff,Ubuff);

    result=copy_from_user(Kbuff,Ubuff,count);

    if (result<0)
    {
        printk("Copy from User failed\n");
        return -1;
    }
    
    printk("Data read by Kernel: %s\n",Kbuff);
    
    return count-result;
}

static int __init insert(void)
{
    int result,major,minor;
    dev_t mydev;
    
    mydev=MKDEV(255,0);
    major=MAJOR(mydev);
    minor=MINOR(mydev);
    
    printk("Inserting Module\n\nMajor=%d\nMinor=%d\n",major,minor);

    result=register_chrdev_region(mydev,1,"mychardrive");

    if(result<0)
    {
        printk("Error registering device\n");
        return result;
    }
    
    my_cdev=cdev_alloc();
    my_cdev->ops=&fops;

    result=cdev_add(my_cdev,mydev,1);

    if(result<0)
    {
        printk("Error adding device");
        unregister_chrdev_region(mydev,1);
        printk("Device unregistered");
        return -1;
    }
    return 0;
}

static void __exit remove(void)
{
    //int major,minor;
    dev_t mydev;
    
    mydev=MKDEV(255,0);
    //major=MAJOR(mydev);
    //minor=MINOR(mydev);
    
    //printk("Major=%d\nMinor=%d\n",major,minor);

    unregister_chrdev_region(mydev,1);

    cdev_del(my_cdev);

    printk("Module removed");    
}


module_init(insert);
module_exit(remove);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RAHUL");
MODULE_DESCRIPTION("Character device");