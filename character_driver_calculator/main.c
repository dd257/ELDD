#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/uaccess.h>
#include<linux/fs.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/cdev.h>
#include<linux/string.h>

int add_open(struct inode *,struct file *);
int add_release(struct inode *,struct file *);
int sub_open(struct inode *,struct file *);
int sub_release(struct inode *,struct file *);
int mul_open(struct inode *,struct file *);
int mul_release(struct inode *,struct file *);
int div_open(struct inode *,struct file *);
int div_release(struct inode *,struct file *);
ssize_t add_read(struct file *,char __user *,size_t,loff_t *);
ssize_t add_write(struct file *,const char __user *,size_t,loff_t *);
ssize_t sub_read(struct file *,char __user *,size_t,loff_t *);
ssize_t sub_write(struct file *,const char __user *,size_t,loff_t *);
ssize_t mul_read(struct file *,char __user *,size_t,loff_t *);
ssize_t mul_write(struct file *,const char __user *,size_t,loff_t *);
ssize_t div_read(struct file *,char __user *,size_t,loff_t *);
ssize_t div_write(struct file *,const char __user *,size_t,loff_t *);

dev_t mydev;

int sum,dif,prod,quot;

struct file_operations add_fops=
{
    .owner=THIS_MODULE,
    .read=add_read,    
    .write=add_write,
    .open=add_open,
    .release=add_release,
};

struct file_operations sub_fops=
{
    .owner=THIS_MODULE,
    .read=sub_read,    
    .write=sub_write,
    .open=sub_open,
    .release=sub_release,
};

struct file_operations mul_fops=
{
    .owner=THIS_MODULE,
    .read=mul_read,    
    .write=mul_write,
    .open=mul_open,
    .release=mul_release,
};

struct file_operations div_fops=
{
    .owner=THIS_MODULE,
    .read=div_read,    
    .write=div_write,
    .open=div_open,
    .release=div_release,
};

struct cdev *add_cdev,*sub_cdev,*mul_cdev,*div_cdev;

int add_open(struct inode *inode,struct file *filp)
{
    printk("\nAdd Open call");
    return 0;
}

int sub_open(struct inode *inode,struct file *filp)
{
    printk("\nSub Open call");
    return 0;
}

int mul_open(struct inode *inode,struct file *filp)
{
    printk("\nMul Open call");
    return 0;
}

int div_open(struct inode *inode,struct file *filp)
{
    printk("\nDiv Open call");
    return 0;
}

int add_release(struct inode *inode,struct file *filp)
{
    printk("Add Release call");
    return 0;
}

int sub_release(struct inode *inode,struct file *filp)
{
    printk("Sub Release call");
    return 0;
}

int mul_release(struct inode *inode,struct file *filp)
{
    printk("Mul Release call");
    return 0;
}

int div_release(struct inode *inode,struct file *filp)
{
    printk("Div Release call");
    return 0;
}

ssize_t add_read(struct file *filp,char __user *Ubuff,size_t count,loff_t *offp)
{
    char Kbuff[20]={};
    int result;

    sprintf(Kbuff,"%d",sum);

    result=copy_to_user(Ubuff,Kbuff,sizeof(Kbuff));

    if (result<0)
    {
        printk("Copy to User failed\n");
        return -1;
    }

    printk("Add data transfer %s\nSum = %s\n",(result>0)?("Incomplete"):("Complete"),Ubuff);

    return count-result;
}

ssize_t sub_read(struct file *filp,char __user *Ubuff,size_t count,loff_t *offp)
{
     char Kbuff[20]={};
    int result;

    sprintf(Kbuff,"%d",dif);

    result=copy_to_user(Ubuff,Kbuff,sizeof(Kbuff));

    if (result<0)
    {
        printk("Copy to User failed\n");
        return -1;
    }

    printk("Sub data transfer %s\nDifference = %s\n",(result>0)?("Incomplete"):("Complete"),Ubuff);

    return count-result;
}

ssize_t mul_read(struct file *filp,char __user *Ubuff,size_t count,loff_t *offp)
{
    char Kbuff[20]={};
    int result;

    sprintf(Kbuff,"%d",prod);

    result=copy_to_user(Ubuff,Kbuff,sizeof(Kbuff));

    if (result<0)
    {
        printk("Copy to User failed\n");
        return -1;
    }

    printk("Multiplication data transfer %s\nProduct = %s\n",(result>0)?("Incomplete"):("Complete"),Ubuff);

    return count-result;
}

ssize_t div_read(struct file *filp,char __user *Ubuff,size_t count,loff_t *offp)
{
    char Kbuff[20]={};
    int result;

    sprintf(Kbuff,"%d",quot);

    result=copy_to_user(Ubuff,Kbuff,sizeof(Kbuff));

    if (result<0)
    {
        printk("Copy to User failed\n");
        return -1;
    }

    printk("Add data transfer %s\nQuotient = %s\n",(result>0)?("Incomplete"):("Complete"),Ubuff);

    return count-result;
}

ssize_t add_write(struct file *filp,const char __user *Ubuff,size_t count,loff_t *offp)
{
    char Kbuff[20]={};
    int i,j=0,num[2]={};
  
    int result=copy_from_user(Kbuff,Ubuff,count);

    if (result<0)
    {
        printk("Copy from User failed\n");
        return -1;
    }
        
    i=strlen(Kbuff)-1;

    for(i;i>=0;i--)
    {
        if(Kbuff[i]!=',')
            num[j]=(Kbuff[i]-48)+num[j]*10;
        else
            j++;
    }

    sum=num[0]+num[1];

    printk("Numbers to add: %d %d\n",num[1],num[0]);
    
    return count-result;
}

ssize_t sub_write(struct file *filp,const char __user *Ubuff,size_t count,loff_t *offp)
{
    char Kbuff[20]={};
    int i,j=0,num[2]={};
  
    int result=copy_from_user(Kbuff,Ubuff,count);

    if (result<0)
    {
        printk("Copy from User failed\n");
        return -1;
    }
        
    i=strlen(Kbuff)-1;

    for(i;i>=0;i--)
    {
        if(Kbuff[i]!=',')
            num[j]=(Kbuff[i]-48)+num[j]*10;
        else
            j++;
    }

    dif=num[1]-num[0];
    
    printk("Numbers to sub: %d %d\n",num[1],num[0]);
    
    return count-result;
}

ssize_t mul_write(struct file *filp,const char __user *Ubuff,size_t count,loff_t *offp)
{
   char Kbuff[20]={};
    int i,j=0,num[2]={};
  
    int result=copy_from_user(Kbuff,Ubuff,count);

    if (result<0)
    {
        printk("Copy from User failed\n");
        return -1;
    }
        
    i=strlen(Kbuff)-1;

    for(i;i>=0;i--)
    {
        if(Kbuff[i]!=',')
            num[j]=(Kbuff[i]-48)+num[j]*10;
        else
            j++;
    }

    prod=num[1]*num[0];
    
    printk("Numbers to multiply: %d %d\n",num[1],num[0]);
    
    return count-result;
}

ssize_t div_write(struct file *filp,const char __user *Ubuff,size_t count,loff_t *offp)
{
    char Kbuff[20]={};
    int i,j=0,num[2]={};
  
    int result=copy_from_user(Kbuff,Ubuff,count);

    if (result<0)
    {
        printk("Copy from User failed\n");
        return -1;
    }
        
    i=strlen(Kbuff)-1;

    for(i;i>=0;i--)
    {
        if(Kbuff[i]!=',')
            num[j]=(Kbuff[i]-48)+num[j]*10;
        else
            j++;
    }

    quot=num[1]/num[0];
    
    printk("Numbers to divide: %d %d\n",num[1],num[0]);
    
    return count-result;
}

static int __init insert(void)
{
    int result,major,minor;

    printk("\n\nInserting Modules\n");

    result=alloc_chrdev_region(&mydev,0,4,"calc_drive");

    if(result<0)
    {
        printk("Error registering device\n");
        return result;
    }
    
    major=MAJOR(mydev);
    minor=MINOR(mydev);

    printk("Major=%d\nMinor=%d\n",major,minor);

    add_cdev=cdev_alloc();
    add_cdev->ops=&add_fops;

    sub_cdev=cdev_alloc();
    sub_cdev->ops=&sub_fops;

    mul_cdev=cdev_alloc();
    mul_cdev->ops=&mul_fops;

    div_cdev=cdev_alloc();
    div_cdev->ops=&div_fops;

    result=cdev_add(add_cdev,MKDEV(major,minor),1);
    if(result<0)
    {
        printk("Error adding Add device");
        unregister_chrdev_region(mydev,4);
        printk("Add Device unregistered");
        return -1;
    }
    printk("Addition device added\n");
    
    result=cdev_add(sub_cdev,MKDEV(major,minor+1),1);
    if(result<0)
    {
        printk("Error adding Sub device");
        unregister_chrdev_region(mydev,4);
        printk("Sub Device unregistered");
        return -1;
    }
    printk("Subtraction device added\n");

    result=cdev_add(mul_cdev,MKDEV(major,minor+2),1);
    if(result<0)
    {
        printk("Error adding Mul device");
        unregister_chrdev_region(mydev,4);
        printk("Mul Device unregistered");
        return -1;
    }
    printk("Multiplcation device added\n");

    result=cdev_add(div_cdev,MKDEV(major,minor+3),1);
    if(result<0)
    {
        printk("Error adding Div device");
        unregister_chrdev_region(mydev,4);
        printk("Div Device unregistered");
        return -1;
    }
    printk("Division device added\n");

    return 0;
}

static void __exit remove(void)
{
    //char major,minor;
    //dev_t mydev;
    
    //mydev=MKDEV(255,0);
    //major=MAJOR(mydev);
    //minor=MINOR(mydev);
    
    //printk("Major=%d\nMinor=%d\n",major,minor);

    unregister_chrdev_region(mydev,4);

    cdev_del(add_cdev);
    cdev_del(sub_cdev);
    cdev_del(mul_cdev);
    cdev_del(div_cdev);

    printk("Modules removed\n");    
}


module_init(insert);
module_exit(remove);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RAHUL");
MODULE_DESCRIPTION("Character device");