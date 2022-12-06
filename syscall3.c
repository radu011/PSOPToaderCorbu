#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/sched.h>
#include<linux/syscalls.h>
#include<linux/module.h>
#include <linux/proc_fs.h>
#include<linux/vmalloc.h>
#define __KERNEL__
SYSCALL_DEFINE1(syscall3,pid_t,pid)
{
    struct task_struct* ts=find_task_by_vpid(pid);
    struct vm_struct *t=ts->stack_vm_area;
    void* start_address=t->addr;
    unsigned long size=t->size;
    printk("\nAdresa de inceput a stackului procesului este:0x%x\nDimensiunea stackului este:%lu\n",start_address,size);
    return 0;
} 
