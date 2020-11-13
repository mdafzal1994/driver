#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>

static int add(int a,int b);

static int __init init_fun(void)
{

printk(KERN_ALERT"inside average   init fun \n");
 add_fun(3,6);
return 0;
}

static void __exit  exit_fun(void)
{

 printk(KERN_ALERT"exit average module fun \n");


}


module_init(init_fun);
module_exit(exit_fun);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("afzal");




