#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>

int main(void)
{
        
    int i=0,j=0,fd,num[2];
    char Ubuff[20]={},Kbuff[20];
    
    printf("Please enter numbers to multiply: ");
    scanf("%d %d",&num[0],&num[1]);

    fd=open("/dev/mul_dev",O_RDWR);

    if(fd<0)
    {
        perror("Error");
        return 0;
    }

    while(num[i])
    {
        Ubuff[j]=(num[i]%10)+48;
        printf("Ubuff[%d]: %c\n",j,Ubuff[j]);
        num[i]=num[i]/10;
    
        if(num[i]=='\0' && i==0)
        {
            j++;
            Ubuff[j]=',';
            i++;    
        }
        j++;
    }
    
    write(fd,Ubuff,sizeof(Ubuff));
    read(fd,Kbuff,0);

    printf("Product: %s\n",Kbuff);

    close(fd);

}