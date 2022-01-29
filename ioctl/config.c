#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include <sys/ioctl.h>
#include"ioctl.h"
#include<stdlib.h>

struct defaultdata
{
    int baudrate;
    int stopbits;
    int direction;
};

int main(int argv, char *argc[])
{        
    int fd,result,stop_bits,direction;
    unsigned long baud_rate;
    char Kbuff[80];

    struct defaultdata tosend;
    
    fd=open("/dev/myioctl",O_RDWR);

    if(fd<0)
    {
        perror("Error");
        return 0;
    }

    if(argv>1)
    {
        baud_rate=atoi(argc[1]);
        stop_bits=atoi(argc[2]);
        direction=atoi(argc[3]);
    }
    else    
    {
        tosend.baudrate=9600;
        tosend.stopbits=1;
        tosend.direction=0;

        result=ioctl(fd,DEFAULT,&tosend);
        if(result<0)
        {
            perror("Error in default values");
            return result;
        }

        read(fd,Kbuff,0);
        printf("Default values set\n");
        printf("Data read from user: %s\nSize of Ubuff: %ld\n",Kbuff,strlen(Kbuff));

        close(fd);
        return 0;
    }        
    
    result=ioctl(fd,BAUD_RATE,&baud_rate);
    if(result<0)
    {
        perror("Error in updating Baud rate");
        return result;
    }
    printf("Baud rate set\n");
    
    result=ioctl(fd,STOP_BITS,&stop_bits);
    if(result<0)
    {
        perror("Error in updating Stop bits");
        return result;
    }
    printf("Stop bits set\n");
    
    result=ioctl(fd,DIRECTION,&direction);
    if(result<0)
    {
        perror("Error in updating direction");
        return result;
    }
    printf("Direction set\n");
    
    //write(fd,Ubuff,sizeof(Ubuff));
    read(fd,Kbuff,0);

    printf("Data read from user: %s\nSize of Ubuff: %ld\n",Kbuff,strlen(Kbuff));

    close(fd);

}