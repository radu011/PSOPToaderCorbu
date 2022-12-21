#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/string.h>
#define __KERNEL__
SYSCALL_DEFINE1(syscall3, struct proces *, procese)
{
	struct task_struct *task;
	int nr = 0;
	int i = 0;
	int success=-1;
	struct proces *procs;
	for_each_process(task) {
		nr++;
	}
	procs = (struct proces *)kmalloc(nr * sizeof(struct proces),
					 GFP_KERNEL);
	printk("Sunt %d procese\n",nr);
	for_each_process(task) {
		snprintf(procs[i].nume, 30, "%s", task->comm);
		procs[i].pid = task->pid;
		procs[i].nice_val = task_nice((const struct task_struct *)task);
		i++;
	}
	success = copy_to_user(procese, procs, nr * sizeof(struct proces));
	if (success != 0)
		return -1;
	return nr;
}
