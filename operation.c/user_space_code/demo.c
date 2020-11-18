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


/*void add(int a,int b)
	{
	
	
	 
	}
*/
int main()
{
	int fd=open("/dev/myd_driver2",O_RDWR);  //read write
        if(fd==-1)
	{
	
	  printf("error : file  not open  / found \n");
	  return 0;
	}

	strcpy(wr_buffer,"33 ");

    	printf("data writing to kernel ........\n");
     	write(fd,wr_buffer,128);  	    
	printf("writing done from user space\n");
	strcpy(wr_buffer,"22");

     	write(fd,wr_buffer,128);  	    
	printf("2 nd writing done from user space\n");
	///////////////////reading /////////////////
	
	  read(fd,rd_buffer,128);
	  printf("reading done \n");

	  printf("read data from driver   %s\n",rd_buffer);

	  close(fd);


return 0 ;
}



