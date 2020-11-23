

/*
 *
 *   uart0 code for driver uart0  205 0 decice number  char device
 *
 */

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
  int fd=open("/dev/uart0",O_RDWR);
       if(fd==-1)

       {
          printf("error : file /dev/uart0 not  open\n");
          return;
        }
	
	
	       printf("max data can read :%d \n HOW many want to read \n",(int)sizeof(rd_buffer));
	      scanf("%d",&SIZE); 
	      
      


/////////////////////////////////
        read(fd,rd_buffer,SIZE);
          

  printf("\nread   data from driver   %s\n",rd_buffer);
  SIZE=strlen(rd_buffer);
  printf("No of BYTE READ : %d\n",SIZE);
          close(fd);

        }

	

int main()
{


	my_read();


return 0 ;
}
