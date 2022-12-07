#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/sched.h>
#include<linux/syscalls.h>
#include<linux/module.h>
#include <linux/proc_fs.h>
#define __KERNEL__
SYSCALL_DEFINE0(syscall4)
{
    struct task_struct *task;
    int nr=0;
    for_each_process(task)
    {
        nr++;
    }
    printk("\nNumarul de procese existente este: %d", nr);
    return 0;
} 
