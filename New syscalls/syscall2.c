#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/vmalloc.h>
#include <linux/mm_types.h>
#define __KERNEL__

SYSCALL_DEFINE2(syscall2, pid_t, pid, struct space_info *, info)
{
	int success;
	struct task_struct *ts = find_task_by_vpid(pid);
	struct vm_struct *t = ts->stack_vm_area;
	struct mm_struct *mm = ts->mm;
	struct space_info *kinfo = (struct space_info *)kmalloc(
		sizeof(struct space_info), GFP_KERNEL);
	kinfo->stack_start = (unsigned long)t->addr;
	kinfo->stack_end = (unsigned long)t->addr + t->size;
	kinfo->heap_start = (unsigned long)mm->start_brk;
	kinfo->heap_end = (unsigned long)mm->brk;
	kinfo->code_start = (unsigned long)mm->start_code;
	kinfo->code_end = (unsigned long)mm->end_code;
	kinfo->data_start = (unsigned long)mm->start_data;
	kinfo->data_end = (unsigned long)mm->end_data;
	success = copy_to_user(info, kinfo, sizeof(struct space_info));
	if (success != 0)
		return -1;
	return 0;
}
