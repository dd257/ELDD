#define MAGIC_NUMBER '0'
#define BAUD_RATE _IOWR(MAGIC_NUMBER,0,int)
#define STOP_BITS _IOWR(MAGIC_NUMBER,1,int)
#define DIRECTION _IOWR(MAGIC_NUMBER,2,int)
#define DEFAULT _IOW(MAGIC_NUMBER,3,int)
