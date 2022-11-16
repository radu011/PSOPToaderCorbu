#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/sched.h>
#include<linux/syscalls.h>
#include<linux/module.h>
#include <linux/proc_fs.h>
#define __KERNEL__
SYSCALL_DEFINE1(syscall2,pid_t,pid)
{
    struct task_struct* proces=find_task_by_vpid(pid);
    printk("%d\n",proces->__state);
    if(proces->__state==0)
        printk("\nNumele procesului: %s\nStarea procesului: RUNNING\n",proces->comm);
    else if((proces->__state&1)||(proces->__state&2))
        printk("\nNumele procesului: %s\nStarea procesului: WAITING\n",proces->comm);
    else if(proces->__state&4)
        printk("\nNumele procesului: %s\nStarea procesului: STOPPED\n",proces->comm);
    else if(proces->__state&64)
        printk("\nNumele procesului: %s\nStarea procesului: FINISHED\n",proces->comm);
    else 
        printk("\nNumele procesului: %s\nStarea procesului: NEDEFINITA (Alta decat RUNNING, WAITING, STOPPED SAU FINISHED)\n",proces->comm);
    return 0;
}