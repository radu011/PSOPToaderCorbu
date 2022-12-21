#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/utsname.h>
#define __KERNEL__
SYSCALL_DEFINE1(syscall5, struct sistem *, sys)
{
	struct new_utsname *uts = utsname();
	struct sistem *ksys =
		(struct sistem *)kmalloc(sizeof(struct sistem), GFP_KERNEL);
	int success = 0;
	snprintf(ksys->nume, 20, "%s", uts->sysname);
	snprintf(ksys->versiune, 10, "%s", uts->release);
	snprintf(ksys->data_actualizare, 70, "%s", uts->version);
	success = copy_to_user(sys, ksys, sizeof(struct sistem));
	if (success != 0)
		return -1;
	return 0;
}
