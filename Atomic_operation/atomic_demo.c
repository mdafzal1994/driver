#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/kthread.h>  // kernel threads
#include<linux/sched.h>  // task struct
#include<linux/delay.h>  




/*   actually  ATOMIC   complete the instruction in one cycle */

static struct task_struct* sthread1;
static struct task_struct* sthread2;

atomic_t  global_variable=ATOMIC_INIT(0);   //taking   varible 

int  thread1(void* temp);
int  thread2(void* temp);




int  thread1(void* temp)
	{    while(!kthread_should_stop())
		{	printk("thread1 ..\n");
			atomic_inc(&global_variable);   // 
			int k=atomic_read(&global_variable);    //
			printk("thread1   %d \n",k);
                     msleep(1000);
		}
	
		return 0;	
	}

int  thread2(void* temp)
	{      while(!kthread_should_stop())
		{printk("thread2 ..\n");
			atomic_inc(&global_variable);
                        int k=atomic_read(&global_variable);
                        printk("thread2   %d \n",k);

		 msleep(1000);
		}
	return 0;
	
	}




static int __init my_init(void)
	{
	  dev_t deviceno=MKDEV(42,0);
		if((register_chrdev_region(deviceno,1,"atomic driver"))<0)
		{
			printk("not register\n");
		
				return -1;
		}
	
	/* create thread   */
		sthread1=kthread_run(thread1,NULL,"my thread1");
		if(sthread1)
		{
			printk("sthraed1 created\n");
			
		}
		else
		{
		  printk("sthread1 not created \n");
		  goto k_reg;
		}
		sthread2=kthread_run(thread2,NULL,"my thread2");
		if(sthread1)
                	{
                        printk("sthraed2 created\n");

                	}
                else
                {
                  printk("sthread2 not created \n");
                  goto k_reg;
                }



	printk("INIT Done \n");	
	return 0;

k_reg:
	unregister_chrdev_region(deviceno,1);
	return -1;
	}

static void __exit my_exit(void)
	{
		dev_t  deviceno=MKDEV(42,0);
		kthread_stop(sthread1);
		kthread_stop(sthread2);
		unregister_chrdev_region(deviceno,1);
		printk("EXIT Done\n");
	
	
	}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("afzal");
MODULE_DESCRIPTION("atomic  and thread ");

