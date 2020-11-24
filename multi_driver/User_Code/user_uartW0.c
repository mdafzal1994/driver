/*
 *
 *  uarto write data 
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
char wr_buffer[128]="hello CDAC how r u";
int SIZE;

 void my_write()
	{
	
	int fd=open("/dev/my_hello",O_RDWR);
       if(fd==-1)
	{
          printf("error :write file /dev/uart0 not open\n");
          return;
        }
	
        
        write(fd,wr_buffer,strlen(wr_buffer));
        //printf("writing done from user space\n);
	SIZE=strlen(wr_buffer);
        printf("total Byte written : %d\n",SIZE);




          close(fd);



	 //printf("add result :%d",rd_buffer);
	}

int main()
{

	my_write();
	  //close(fd);


return 0 ;
}
