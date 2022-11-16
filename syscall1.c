#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/sched.h>
#include<linux/syscalls.h>
#include<linux/module.h>
#include <linux/proc_fs.h>
#define __KERNEL__
SYSCALL_DEFINE1(syscall1,pid_t,pid)
{
    struct task_struct*parent;
    struct task_struct*proces;
    for_each_process(proces){
        if(proces->pid==pid){
           parent=proces->real_parent;
           break;
        }
    }
    printk("\nNumele procesului: %s\nNumele procesului parinte: %s\nPidul procesului parinte: %d",proces->comm,parent->comm,parent->pid);
    return 0;
}