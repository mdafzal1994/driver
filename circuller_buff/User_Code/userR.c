#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fcntl.h>
#include <string.h>



char rd_buffer[128];
char wr_buffer[128];
int SIZE;
void my_read()
	{
  int fd=open("/dev/Circuler1",O_RDWR);
       if(fd==-1)

       {
          printf("error : file /dev/circuller not  open\n");
          return;
        }
	
	
	        
      


/////////////////////////////////
        read(fd,rd_buffer,10);
          

  printf("read   data from driver   %s\n",rd_buffer);
  SIZE=strlen(rd_buffer);
  printf("No of BYTE READ : %d\n",SIZE);
          close(fd);

        }

	

int main()
{


	my_read();


return 0 ;
}
