#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argv, char *argc[])
{        
    int fd;
    char Kbuff[80]={}; 

    fd=open("/dev/wait_queue",O_RDWR);

    if(fd<0)
    {
        perror("Error");
        return 0;
    }

    write(fd,argc,sizeof(char));
    read(fd,Kbuff,0);

    printf("Data read from user: %s\nSize of Ubuff: %ld\n",Kbuff,strlen(Kbuff));

    close(fd);
    return 0;
}