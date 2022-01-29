#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/uaccess.h>
#include<linux/fs.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/cdev.h>
#include<linux/ioctl.h>
#include<linux/wait.h>

int device_open(struct inode *,struct file *);
int device_release(struct inode *,struct file *);
ssize_t device_read(struct file *,char __user *,size_t,loff_t *);
ssize_t device_write(struct file *,const char __user *,size_t,loff_t *);
dev_t mydev;
wait_queue_head_t device_queue;
char *flag;

struct file_operations fops=
{
    .owner=THIS_MODULE,
    .read=device_read,    
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

ssize_t device_read(struct file *filp,char __user *Ubuff,size_t count,loff_t *offp)
{
    char Kbuff[]="Wait is over";

    int result;
    
    wake_up(&device_queue);

    result=copy_to_user(Ubuff,Kbuff,sizeof(Kbuff));

    if (result<0)
    {
        printk("Copy to User failed\n");
        return -1;
    }

    printk("Data read by User %s\nFlag: %d\n",(result>0)?("Incomplete"):("Complete"),flag);

    return count-result;
}

ssize_t device_write(struct file *filp,const char __user *Ubuff,size_t count,loff_t *offp)
{
    char Kbuff[80];
    int result;

    result=copy_from_user(Kbuff,Ubuff,count);
    sprintf(flag,"%c",Kbuff);

    if (result<0)
    {
        printk("Copy from User failed\n");
        return result;
    }

    printk("Flag: %s",Kbuff);
    return 0;
}

static int __init insert(void)
{
    int result,major,minor;
    
    printk(KERN_ALERT "\nInserting Module\n");
    result=alloc_chrdev_region(&mydev,0,1,"/dev/wait_queue");

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
        return result;
    }

    init_waitqueue_head(&device_queue);
    printk("waitqueue\n");
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
MODULE_DESCRIPTION("Wait queues");