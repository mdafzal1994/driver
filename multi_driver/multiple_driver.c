#include<linux/kernel.h>
#include<linux/module.h>		// modules  init ,exit
#include<linux/fs.h>			// register   unregister
#include<linux/slab.h>			// kmalloc
#include<linux/wait.h>			//wait queue
#include<linux/circ_buf.h>		//circuler buffer
#include<linux/cdev.h>			//cdev add ,init
#include<linux/uaccess.h>		//user to/from kernel





#define MAJORN    205   //major number
#define NMINORS   3    	//minors number 0,1,2
#define SIZE	  32	//kernel bufffer size
dev_t device_no;//device number
struct my_device{
		struct cdev my_cdev;
		wait_queue_head_t my_waitq;
		struct circ_buf my_buff;

		}_dev[NMINORS];



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
			int ret,i,j,tempd;
			device_no=MKDEV(MAJORN,0);
			ret=register_chrdev_region(device_no,NMINORS,"my multi driver");
			if(ret<0)
				{
					printk("file not register\n");
					goto reg_out;
				}
			for(i=0;i<NMINORS;i++)
			{
				cdev_init(&_dev[i].my_cdev,&my_operation);
				_dev[i].my_buff.buf=kmalloc(SIZE,GFP_KERNEL);  // memory allocate seperate for each device	
				if(!_dev[i].my_buff.buf)    //NULL checking
				{
					printk("error memory not allocating \n");
					goto	cbuf_out;
				}

				init_waitqueue_head(&_dev[i].my_waitq);
			}

			for(j=0;j<NMINORS;j++)
			{
				tempd=MKDEV(MAJOR(device_no),MINOR(device_no)+j);
				ret=cdev_add(&_dev[i].my_cdev,tempd,1);
				if(ret<0)
				{
					printk("error unable to add cdev\n");
					goto cadd_out;
				
				}
			
			
			}
                      printk("INIT Done\n");
		
		return 0;

	cadd_out:
		for(--j;j>=0;--j)
		{
			cdev_del(&_dev[j].my_cdev);
		}
	cbuf_out :
		for(--i;i>=0;--i)
		{
			kfree(&_dev[i].my_buff.buf);
			
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
			
			cdev_del(&_dev[i].my_cdev);
		        kfree(_dev[i].my_buff.buf);
		}

                	unregister_chrdev_region(device_no,NMINORS);
          printk("exit DONE : \n");

	}

static int my_open(struct inode *inodep, struct file *filep)
        {
               
	//	struct my_device *devp=container_of(inodep->i_cdev,struct my_device,my_cdev);

                printk("enter my_open \n");
//		filep->private_data=devp;
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
		int k=0;
	//	struct my_device  *_devp=filep->private_data;
	  	printk("enter my_read\n");
/*	//	printk("tail %d  head %d \n",my_buff.tail,my_buff.head);
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
		*/
		return k;
	
	
	
	}
ssize_t my_write(struct file *filep, const char __user *ubuff, size_t cnt, loff_t *offset)
	{
		          
		int i=0;
		int ret;
		int k;
//		struct my_device *_devp=filep->private_data;
		printk("enter my_write \n");
//		printk("before write head   %d   tail %d",my_buff.head,my_buff.tail);
/*		printk("SPACE AVILABLE : %d\n",CIRC_SPACE(_devp->my_buff.head,_devp->my_buff.tail,SIZE));
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
		wake_up(&_devp->my_waitq); */
		return i;
	
	}





module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("afzal");
MODULE_DESCRIPTION("use of circuller buffer");



