/* user space application for testing my driver code   
 * */



#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fcntl.h>
#include <string.h>



char rd_buffer[128];
char wr_buffer[128];
int main()
{
	int fd=open("/dev/my_deriver2",O_RDWR);  //read write
        if(fd==-1)
	{
	
	  printf("error : file  not open\n");
	  return 0;
	}

	strcpy(wr_buffer,"hello CDAC ");

    	printf("data writing to kernel ........\n");
     	write(fd,wr_buffer,128);  	    
	printf("writing done from user space\n");

	///////////////////reading /////////////////
	
	  read(fd,rd_buffer,128);
	  printf("reading done \n");

	  printf("read data from driver   %s\n",rd_buffer);

	  close(fd);


return 0 ;
}



