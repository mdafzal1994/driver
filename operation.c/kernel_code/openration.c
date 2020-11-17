#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/slab.h> //kmalloc  and 
#include<linux/gfp.h>  // malloc flage
#include<linux/uaccess.h>//  copy to/from user 


struct cdev *mycdev;
dev_t device_no;
int *kernel_buffer;  //
size_t mem_size=128;  //



int open_fun(struct inode *inode, struct file *file)
	{
		printk(KERN_ALERT"open fun run\n");
		kernel_buffer=kmalloc(mem_size,GFP_KERNEL);//Allocate normal kernel ram     
		if(kernel_buffer==0)
		{
			printk(KERN_ALERT"error : kernel meemory not alloacted \n");
		return -1;
		}
	
	 return 0;
	}
ssize_t read_fun(struct file *file, char __user *buf,size_t len, loff_t *ppos)
	{
	
		printk(KERN_ALERT"read fun run \n");
		copy_to_user(buf, kernel_buffer,mem_size);
		printk(KERN_ALERT"data read done from kernel to user \n");
		return mem_size;
	}
ssize_t write_fun(struct file *file, const char __user *buf,size_t len, loff_t *ppos)
		{
	
			printk(KERN_ALERT"write fun run\n");
			copy_from_user(kernel_buffer,buf,mem_size);
			printk(KERN_ALERT"data write : done %s\n",buf);
	         return len;
	
		}
int release_fun(struct inode *inode, struct file *file)
	{
		 printk(KERN_ALERT"relase fun run\n");
		 kfree(kernel_buffer); //kernel buffer
		 printk(KERN_ALERT"kernel buffer free\n");
	return 0;
	}


static const struct file_operations my_operation= {                          
        .owner   = THIS_MODULE,                                         
        .open    = open_fun,                                     
        .release = release_fun,                                 
        .read    = read_fun,                                    
        .write   = write_fun,                                   
       // .llseek  = generic_file_llseek,                                 
};



static int __init init_fun(void)
	{
		printk(KERN_ALERT"enter init fun \n");

		 device_no=MKDEV(228,0);
		if(register_chrdev_region(device_no,1,"my driver operation\n")<0)
		{
		
		  printk(KERN_ALERT"error : register not get region \n");
		  return -1;
		
		}
	
		/////////////////////////////////
		mycdev=cdev_alloc();
		
		mycdev->ops=&my_operation;

		///////////////////////
		if(cdev_add(mycdev,device_no,1)<0)
		{
		   printk(KERN_ALERT"error : cdev is not add \n");
		   unregister_chrdev_region(device_no,1);
		   return -1;
		
		}
            else 
		  printk(KERN_ALERT" cdev is add succ  \n");


  	return 0;
	}

static void __exit exit_fun(void)
	{
		printk(KERN_ALERT"exit fun run \n");
		cdev_del(mycdev);
	       unregister_chrdev_region(device_no,1);
	
	
	}

module_init(init_fun);
module_exit(exit_fun);



MODULE_LICENSE("GPL");
MODULE_AUTHOR("afzal");
MODULE_DESCRIPTION("operation open read write for user\n");
