#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/circ_buf.h>
#include<linux/slab.h>
#include<linux/uaccess.h>




struct cdev my_cdev;
struct circ_buf my_buff;
int SIZE=32;

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



static int __init  init_fun(void )
	{
	            
       		dev_t device_no=MKDEV(208,0);

	   	printk("init enter\n")	;
               if(register_chrdev_region(device_no,1,"my circulller buffer")<0)
	       {
	       
	          printk("error not register\n");
		  return -1;
	       
	       }

                  ////////////////////// create circuler buffer  ////////
		  my_buff.buf=kmalloc(SIZE,GFP_KERNEL);    //GFP_KERNEL  means Allocate normal kernel ram.
                   if(!my_buff.buf)
		   {
		      printk("memory kenel buff not allocate \n");
		      unregister_chrdev_region(device_no,1);
		      return -1;
		   
		   }

           	cdev_init(&my_cdev,&my_operation);	
	 	if(cdev_add(&my_cdev,device_no,1))
		{
			printk("error : cdev not add \n");
			unregister_chrdev_region(device_no,1);
		return -1;
		
		}
		printk("init DONE\n")  ;

	 return 0;
	}



static void __exit  exit_fun(void)
	{   	dev_t device_no=MKDEV(208,0);
		unregister_chrdev_region(device_no,1);
		kfree(my_buff.buf);
	  printk("exit DONE : \n");
	  
	}


static int my_open(struct inode *inode, struct file *file)
	{
		printk("enter my_open \n");
		return 0;

	}	
static  int my_release(struct inode *inode, struct file *file)
	{
		printk("enter my_release \n");
	  return 0;
	
	
	}
ssize_t my_read(struct file *file, char __user *ubuff, size_t cnt, loff_t *offset)
	{
		int i;
		int ret;
		int k=0;
	  	printk("enter my_read\n");
		printk("tail %d  head %d \n",my_buff.tail,my_buff.head);
                printk("kernel buffer count %d \n",CIRC_CNT(my_buff.head,my_buff.tail,SIZE));
		
		
		k=min((int)cnt,CIRC_CNT(my_buff.head,my_buff.tail,SIZE));
		for(i=0;i<k;i++)
		{
		   ret=copy_to_user(ubuff+i,my_buff.buf+my_buff.tail,1);
		   if(ret)
		   {
		   	printk("error copy_to_user \n");
			return -1;
		  }
                  my_buff.tail=(my_buff.tail+1)&(SIZE-1);
		}

                printk("total BYTE write from kernel : %d\n",i);


		return cnt;
	
	
	
	}
ssize_t my_write(struct file *file, const char __user *ubuff, size_t cnt, loff_t *offset)
	{
		          
		int i;
		int ret;

		printk("enter my_write \n");
		printk("before write head   %d   tail %d",my_buff.head,my_buff.tail);
		for(i=0;i<cnt;i++)
		{printk("HEAD    ;%d \n",my_buff.head);
			ret=copy_from_user(my_buff.buf+my_buff.head,ubuff+i,1);
		        if(ret)
			{
			 	printk("error copy from user \n");
				return -EFAULT;
			}
			my_buff.head=(my_buff.head+1)&(SIZE-1);  //

		}
		//printk("before write head   %d   tail %d",my_buff.head,my_buff.tail);
                printk("byte copy to kernel : %d \n %s  \n",i,my_buff.buf);

		printk("after write head   %d   tail %d",my_buff.head,my_buff.tail);
		return i;
	
	}





module_init(init_fun);
module_exit(exit_fun);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("afzal");
MODULE_DESCRIPTION("use of circuller buffer");
