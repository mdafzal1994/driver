#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fcntl.h>
#include <string.h>



char rd_buffer[128];
char wr_buffer[128];






 void add(int a,int b)
	{
	
	int fd=open("/dev/AddDev",O_RDWR);
       if(fd==-1)

       {
          printf("error : file /AddDev not open\n");
          return;
        }
	sprintf(wr_buffer,"%d",a);
        //wr_buffer[0]=a;
        printf("data writing to kernel ........\n");
        write(fd,wr_buffer,128);
        //printf("writing done from user space\n");
        sprintf(wr_buffer,"%d",b);
        write(fd,wr_buffer,128);	


/////////////////////////////////
	read(fd,rd_buffer,128);
          printf("reading done \n");

          printf("read data from driver   %s\n",rd_buffer);

          close(fd);



	 //printf("add result :%d",rd_buffer);
	}

int main()
{
	

	add(5,6);

	  //close(fd);


return 0 ;
}
