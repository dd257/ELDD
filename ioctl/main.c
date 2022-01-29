#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/uaccess.h>
#include<linux/fs.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/cdev.h>
#include<linux/ioctl.h>
#include"ioctl.h"

int device_open(struct inode *,struct file *);
int device_release(struct inode *,struct file *);
ssize_t device_read(struct file *,char __user *,size_t,loff_t *);
long device_ioctl(struct file *,unsigned int,unsigned long);
dev_t mydev;

struct file_operations fops=
{
    .owner=THIS_MODULE,
    .read=device_read,    
    .unlocked_ioctl=device_ioctl,
    .open=device_open,
    .release=device_release,
};

struct defaultdata
{
    int baudrate;
    int stopbits;
    int direction;
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

ssize_t device_read(struct file *filp,char __user *Ubuff,size_t count,loff_t *offp)
{
    char Kbuff[]="File configurations updated";

    int result;
    //ssize_t retval;

    result=copy_to_user(Ubuff,Kbuff,sizeof(Kbuff));

    if (result<0)
    {
        printk("Copy to User failed\n");
        return -1;
    }

    printk("Data read by User %s: %s\n",(result>0)?("Incomplete"):("Complete"),Ubuff);

    return count-result;
}

long device_ioctl(struct file *filp,unsigned int cmd,unsigned long arg)
{
    char Ubuff[80];
    int result,temp;
    //ssize_t retval;

    //strcpy(Kbuff,Ubuff);

    struct defaultdata *tosend;

    switch(cmd)
    {
        case BAUD_RATE:
            get_user(temp,(int __user*)arg);
            tosend->baudrate=temp;
            printk("Baud rate set: %d\n",tosend->baudrate);
            break;

        case STOP_BITS:
            get_user(temp,(int __user*)arg);
            tosend->stopbits=temp;
            printk("Stop bits set: %d\n",tosend->stopbits);
            break;

        case DIRECTION:
            get_user(temp,(int __user*)arg);
            tosend->direction=temp;
            printk("Direction set: %d\n",tosend->direction);
            break;

        case DEFAULT:
            copy_from_user(Ubuff,(struct defaultdata *)arg,sizeof(struct defaultdata));
            tosend=(struct defaultdata *)Ubuff;
            printk("Default data: %d %d %d\n",tosend->baudrate,tosend->stopbits,tosend->direction);
            break;
        
        default:
            printk(KERN_ALERT "Command not found\n");

    }

    return 0;
}

static int __init insert(void)
{
    int result,major,minor;
    
    printk(KERN_ALERT "\nInserting Module\n");
    result=alloc_chrdev_region(&mydev,0,1,"/dev/myioctl");

    if(result<0)
    {
        printk("Error registering device\n");
        return result;
    }
    
    major=MAJOR(mydev);
    minor=MINOR(mydev);

    printk("Major=%d\nMinor=%d\n",major,minor);

    my_cdev=cdev_alloc();
    my_cdev->ops=&fops;

    result=cdev_add(my_cdev,(int)mydev,1);
    
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
    unregister_chrdev_region(mydev,1);

    cdev_del(my_cdev);

    printk(KERN_ALERT "\nModule removed");    
}


module_init(insert);
module_exit(remove);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RAHUL");
MODULE_DESCRIPTION("IOCTL");