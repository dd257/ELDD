#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>

int main(void)
{
        
    int fd;

    char Ubuff[80],Kbuff[80];

    printf("Please enter message for Kernel: ");
    scanf("%s",Ubuff);
    fd=open("/dev/mychardrive",O_RDWR);

    if(fd<0)
    {
        perror("Error");
        return 0;
    }

    write(fd,Ubuff,sizeof(Ubuff));
    read(fd,Kbuff,0);

    printf("Data read from user: %s\nSize of Ubuff: %ld\n",Ubuff,strlen(Ubuff));

    close(fd);

}