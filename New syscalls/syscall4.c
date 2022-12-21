#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uidgid.h>
#include <linux/cred.h>
#define __KERNEL__
SYSCALL_DEFINE1(syscall4, int *, useri)
{
	struct task_struct *task;
	int *kusers = (int *)kmalloc(50 * sizeof(int), GFP_KERNEL);
	int nr_useri = 0;
	int success = 0;
	for_each_process(task) {
		uid_t user = task->cred->uid.val;
		int ok = 1;
		for (int i = 0; i < nr_useri; i++) {
			if (kusers[i] == user) {
				ok = 0;
				break;
			}
		}
		if (ok == 1) {
			kusers[nr_useri++] = user;
		}
	}
	printk("%d\n",nr_useri);
	success = copy_to_user(useri, kusers, nr_useri*sizeof(int));
	if (success != 0)
		return -1;
	return nr_useri;
}
