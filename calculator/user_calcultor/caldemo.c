#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fcntl.h>
#include <string.h>



char rd_buffer[128];
char wr_buffer[128];

void mul(int a,int b)
	{
  int fd=open("/dev/MulDev",O_RDWR);
       if(fd==-1)

       {
          printf("error : file /muldDev not mul open\n");
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

  printf("read multipli  data from driver   %s\n",rd_buffer);

          close(fd);

        }

	
	

void sub(int a,int b)
        {

        int fd=open("/dev/SubDev",O_RDWR);
       if(fd==-1)

       {
          printf("error : file /AddDev not sub open\n");
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

  printf("read sub data from driver   %s\n",rd_buffer);

          close(fd);

	}

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
 	 sub(9,5);

	 mul(8,4);
	  //close(fd);


return 0 ;
}
