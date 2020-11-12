#include<linux/kernel.h>
#include<linux/printk.h>
#include <linux/module.h>

static int var1=5;


module_param(var1,int,S_IRUGO);

static int  init_fun(void)
{

        printk(KERN_ALERT"INIT FUNCTION RUN  %d\n",var1);




return 0;
}

static void exit_fun(void)
{

    printk(KERN_ALERT"exit function run \n");


}


module_init(init_fun);
module_exit(exit_fun);


