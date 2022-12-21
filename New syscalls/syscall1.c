#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/string.h>
#define __KERNEL__

SYSCALL_DEFINE2(syscall1, pid_t, pid, struct proc_info *, info)
{
	int success = -1;
	struct task_struct *proces = find_task_by_vpid(pid);
	struct task_struct *parent = proces->real_parent;
	struct proc_info *proc = (struct proc_info *)kmalloc(
		sizeof(struct proc_info), GFP_KERNEL);
	proc->parent_pid = parent->pid;

	if (proces->__state == 0) {
		success = snprintf(proc->state, 30, "%s", "RUNNING");
	} else if ((proces->__state & 1) || (proces->__state & 2)) {
		success = snprintf(proc->state, 30, "%s", "WAITING");
	} else if (proces->__state & 4) {
		success = snprintf(proc->state, 30, "%s", "STOPPED");
	} else if (proces->__state & 64) {
		success = snprintf(proc->state, 30, "%s", "FINISHED");
	} else {
		success = snprintf(proc->state, 30, "%s", "UNDEFINED");
	}
	if (success < 0)
		return -1;

	success = snprintf(proc->proc_name, 30, "%s", proces->comm);
	if (success < 0)
		return -1;

	success = snprintf(proc->parent_name, 30, "%s", parent->comm);
	if (success < 0)
		return -1;
	success = copy_to_user(info, proc, sizeof(struct proc_info));
	if (success != 0)
		return -1;
	return 0;
}
