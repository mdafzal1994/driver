#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/circ_buf.h>
#include<linux/slab.h>
#include<linux/uaccess.h>
#include<linux/wait.h>
#include<linux/timer.h>

#define TIMER 5000   //5000 msec

struct cdev my_cdev;
struct circ_buf my_buff;
int SIZE=32;

static struct timer_list  chr_timer;
static  wait_queue_head_t my_waitq;
static int my_open(struct inode *inode, struct file *file);
       
static  int my_release(struct inode *inode, struct file *file);
ssize_t my_read(struct file *file, char __user *ubuff, size_t cnt, loff_t *offset);
ssize_t my_write(struct file *file, const char __user *ubuff, size_t cnt, loff_t *offset);






 void callback_timer_fun(struct timer_list* timerp);
 void callback_timer_fun(struct timer_list* timerp)
 	{
	       printk("hello afzal");

	       //re-initilizing the timer  
		mod_timer(&chr_timer,TIMER);	
	
	
	
	}

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
	            
       		dev_t device_no=MKDEV(205,0);

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
	//	init_waitqueue_head(&my_waitq);

	
		/*timer set up   */
		timer_setup(&chr_timer,callback_timer_fun,0);
	      // set intervall   for 
	      mod_timer(&chr_timer,TIMER);	


		printk("init DONE\n")  ;

	 return 0;
	}



static void __exit  exit_fun(void)
	{   	dev_t device_no=MKDEV(205,0);
		unregister_chrdev_region(device_no,1);
		kfree(my_buff.buf);
		del_timer(&chr_timer);
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
			return k;
	
	
	
	}
ssize_t my_write(struct file *file, const char __user *ubuff, size_t cnt, loff_t *offset)
	{
		          
		int i=0;
		int ret;
		int k;
		printk("enter my_write \n");
//	
		return i;
	
	}





module_init(init_fun);
module_exit(exit_fun);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("afzal");
MODULE_DESCRIPTION("use of circuller buffer");
