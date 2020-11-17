#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/cdev.h>
#include<linux/fs.h>

int my_file_open(struct inode *inode, struct file *file)
        {
           printk("char file  is open \n");
           return 0;
        }


int my_file_close(struct inode *inode, struct file *file)
        {
          printk("char file is close \n");
          return 0;  
        }

ssize_t my_file_read(struct file *file, char __user *buffur,size_t lenght, loff_t *offset)
        {
          printk("char file read \n");
          return lenght;
        }

ssize_t my_file_write(struct file *file, const char __user *buf,size_t len, loff_t *ppos)
        {
              printk("char file Write \n");
              return len;

        }



 struct file_operations my_file_operation = {
        .owner   = THIS_MODULE,
        .open    = my_file_open,
        .release = my_file_close,
        .read    = my_file_read,
        .write   = my_file_write,

};


struct cdev *mycdev;  //
//dev_t device_no=MKDEV(230,0);
static int __init init_fun(void)
        {

	dev_t device_no=MKDEV(232,0);

       printk(KERN_ALERT"init run\n");
         // dev_t device_no=MKDEV(240,0);  //mjor 240 min 0

          register_chrdev_region(device_no,1,"my_module111");
         printk(KERN_ALERT"devie is register\n");

          mycdev=cdev_alloc();  //memory alloc
          mycdev->ops=&my_file_operation;
          if(cdev_add(mycdev,device_no,1)<0)
          {
              printk(KERN_ALERT"memory not allocted for cdev\n");


          }
        
        return 0;
        }





static void __exit exit_fun(void)
        {
		 dev_t device_no=MKDEV(232,0);
           unregister_chrdev_region(device_no,1);
             cdev_del(mycdev);
           printk(KERN_ALERT"exit fun run device no :  %d \n",device_no);
        }


module_init(init_fun);
module_exit(exit_fun);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("read write");
MODULE_AUTHOR("afzal");


