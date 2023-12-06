#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/sched.h>
#include<linux/pid.h>

static int init_hello(void){
	printk(KERN_ALERT "Hello Kernel!\n");
	return 0;
}

static void exit_hello(void){
	printk(KERN_ALERT "Bye!\n");
}

void log_pid(struct pid* p){
	printk("fork : pid_vnr= %d, pid_nr=%d\n",pid_wnr(p), pid_nr=(p));
}


module_init(init_hello);
module_exit(exit_hello);
MODULE_LICENSE("GPL");
