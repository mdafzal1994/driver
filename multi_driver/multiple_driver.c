/*#include<linux/kernel.h>
#include<linux/module.h>		// modules  init ,exit
#include<linux/fs.h>			// register   unregister
#include<linux/slab.h>			// kmalloc
#include<linux/wait.h>			//wait queue
#include<linux/circ_buf.h>		//circuler buffer
#include<linux/cdev.h>			//cdev add ,init
#include<linux/uaccess.h>		//user to/from kernel

*/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/circ_buf.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <linux/wait.h>



#define MAJORN    42   //major number
#define NMINORS   3   	//minors number 0,1,2
#define SIZE	  32	//kernel bufffer size
static dev_t device_no;//device number
struct my_device
		{
		struct cdev my_cdev;
		wait_queue_head_t my_waitq;
		struct circ_buf my_buff;
               // int x;
		}s1[NMINORS];



//#define SIZE 32
//#define MAJORN 42
//#define NMINORS 3
/*
static dev_t devnum;      // device number
struct mydevice
{
	struct cdev _cdev;
	//struct circ_buf cbuf; 
	wait_queue_head_t _wq;

	struct circ_buf cbuf; 
	//wait_queue_head_t _wq;
}_devs[NMINORS];
*/
static int my_open(struct inode *inode, struct file *file);
static  int my_release(struct inode *inode, struct file *file);
ssize_t my_read(struct file *file, char __user *ubuff, size_t cnt, loff_t *offset);
ssize_t my_write(struct file *file, const char __user *ubuff, size_t cnt, loff_t *offset);



static const struct file_operations my_operation = {
        .owner   = THIS_MODULE,
        .open    = my_open,
        .release = my_release,
        .read    = my_read,
        .write   = my_write,
        //.llseek  = generic_file_llseek,                                 
};



static int __init my_init(void)
		{
			int ret,i,j;
			dev_t tempd;
			device_no=MKDEV(MAJORN,0);
			ret=register_chrdev_region(device_no,NMINORS,"my multi driver");
			if(ret<0)
				{
					printk("file not register\n");
					return -1;
				//	goto reg_out;
				}
		
			
/*
			cdev_init(&s1.my_cdev,&my_operation);

				ret=cdev_add(&s1.my_cdev,device_no,1);
				if(ret<0)
                                {
                                        printk("error unable to add cdev\n");
					return -1;
                                  //      goto cadd_out;
                                
                                }
			s1.x=25;
			printk("my data %d\n",s1.x);
*/			


/*

     int i,j,ret;
        dev_t tmpdev;
	devnum =MKDEV(MAJORN,0); // is used for constructing a device number
	
	ret = register_chrdev_region(devnum,NMINORS,"my_dev");// request the kernel
	if(ret)
	{  //non zero means not successfull
		printk("Kernel did't grant us device number\n");
		goto reg_out;
	}
	//Control : we got device number
	for(i=0;i<NMINORS;i++)
	{
		cdev_init(&_devs[i]._cdev,&my_operation); // Binds your cdev withfile operations
		_devs[i].cbuf.buf = kmalloc(SIZE,GFP_KERNEL) ;//allocates memory
		if(!_devs[i].cbuf.buf)
		{
			printk("Memory is not allocated\n");
			goto cbuf_out;
		}
		init_waitqueue_head(&_devs[i]._wq);// init our waitqueue
	} // end offirst for loop

	for(j=0;j<NMINORS;j++)
	{
		tmpdev = MKDEV(MAJOR(devnum),MINOR(devnum)+j);
		ret = cdev_add(&_devs[j]._cdev,tmpdev,1); //Device is "Live" Now
		if(ret)
		{
			printk("Unable to add cdev to kernel\n");
			goto cdev_out;
		}
	}
	printk("Done Init\n");
	return 0;

	cdev_out:
	for(--j;j>=0;j--)
		cdev_del(&_devs[j]._cdev);
	
	cbuf_out:
	for(--i;i>=0;i--)
		kfree(_devs[i].cbuf.buf);
	
	reg_out:
		unregister_chrdev_region(devnum,NMINORS);
	return -1;
*/


				for(i=0;i<NMINORS;i++)
			{
				cdev_init(&s1[i].my_cdev,&my_operation);
				s1[i].my_buff.buf=kmalloc(SIZE,GFP_KERNEL);  // memory allocate seperate for each device	
				if(!s1[i].my_buff.buf)    //NULL checking
				{
					printk("error memory not allocating \n");
					goto	cbuf_out;
				}

				init_waitqueue_head(&s1[i].my_waitq);
				printk("test\n");
			}

			for(j=0;j<NMINORS;j++)
			{
				tempd=MKDEV(MAJOR(device_no),MINOR(device_no)+j);
				ret=cdev_add(&s1[j].my_cdev,tempd,1);
				if(ret<0)
				{
					printk("error unable to add cdev\n");
					goto cadd_out;
				
				}
				printk("test2\n");
			
			
			}
                    printk("INIT Done\n");
		
		return 0;

	cadd_out:
		for(--j;j>=0;--j)
		{
			cdev_del(&s1[j].my_cdev);
		}
	cbuf_out :
		for(--i;i>=0;--i)
		{
			kfree(&s1[i].my_buff.buf);
			
		}
	reg_out:	

		unregister_chrdev_region(device_no,NMINORS);  //unregister all device
		return -1; 
}


static void __exit my_exit(void)
	{ 	
		int i;
		for(i=0;i<NMINORS;i++)
		{	
			
			cdev_del(&s1[i].my_cdev);
		        kfree(s1[i].my_buff.buf);
		}

                	unregister_chrdev_region(device_no,1);
          
  printk("exit deon \n");
	}

static int my_open(struct inode *inodep, struct file *filep)
        {
               
		struct my_device *_devp =container_of(inodep->i_cdev,struct my_device,my_cdev);
	filep->private_data = _devp;
	printk("Sample Open function\n");
                return 0;

        }
static  int my_release(struct inode *inodep, struct file *filep)
        {
                printk("enter my_release \n");
          return 0;


        }
ssize_t my_read(struct file *filep, char __user *ubuff, size_t cnt, loff_t *offset)
	{
	
		int i;
		int ret;
		int k;
		struct my_device* _devp=filep->private_data;
	  	printk("enter my_read\n");
//		printk("tail %d  head %d \n",my_buff.tail,my_buff.head);
        //      printk("kernel buffer count %d \n",CIRC_CNT(my_buff.head,my_buff.tail,SIZE));
		
		wait_event_interruptible(_devp->my_waitq,CIRC_CNT(_devp->my_buff.head,_devp->my_buff.tail,SIZE)>0);
		
		k=min((int)cnt,CIRC_CNT(_devp->my_buff.head,_devp->my_buff.tail,SIZE)); //
		for(i=0;i<k;i++)
		{
		   ret=copy_to_user(ubuff+i,_devp->my_buff.buf+_devp->my_buff.tail,1);
		   if(ret)
		   {
		   	printk("error copy_to_user \n");
			return -1;
		  }
                  _devp->my_buff.tail=(_devp->my_buff.tail+1)&(SIZE-1);
		}

                printk("total BYTE write from kernel : %d\n",i);


		wake_up(&_devp->my_waitq);
		
		return k;
	
	
	
	}
ssize_t my_write(struct file *filep, const char __user *ubuff, size_t cnt, loff_t *offset)
	{
		          
		int i=0;
		int ret;
		int k;
		struct my_device *_devp=filep->private_data;
		printk("enter my_write \n");
//		printk("before write head   %d   tail %d",my_buff.head,my_buff.tail);
//		printk("SPACE AVILABLE : %d\n",CIRC_SPACE(_devp->my_buff.head,_devp->my_buff.tail,SIZE));
		 wait_event_interruptible(_devp->my_waitq,CIRC_SPACE(_devp->my_buff.head,_devp->my_buff.tail,SIZE)>1);
		 printk("test\n");

		k=min((int)cnt,CIRC_SPACE(_devp->my_buff.head,_devp->my_buff.tail,SIZE)); //
		for(i=0;i<k;i++)
		{printk("HEAD    ;%d \n",_devp->my_buff.head);
			ret=copy_from_user(_devp->my_buff.buf+_devp->my_buff.head,ubuff+i,1);
		        if(ret)
			{
			 	printk("error copy from user \n");
				return -EFAULT;
			}
			_devp->my_buff.head=(_devp->my_buff.head+1)&(SIZE-1);  //

		}
		//printk("before write head   %d   tail %d",my_buff.head,my_buff.tail);
                //printk("byte copy to kernel : %d \n %s  \n",i,my_buff.buf);

		//printk("after write head   %d   tail %d",my_buff.head,my_buff.tail);
		wake_up(&_devp->my_waitq); 
		return i;
	
	}





module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("afzal");
MODULE_DESCRIPTION("use of circuller buffer");



