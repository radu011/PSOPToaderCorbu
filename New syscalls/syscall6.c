#include <linux/init.h>
#include <linux/module.h> 
#include <linux/sched.h>
#include <linux/rcupdate.h>
#include <linux/fdtable.h>
#include <linux/fs.h> 
#include <linux/fs_struct.h>
#include <linux/dcache.h>
#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/proc_fs.h>
#include <fdtable.h>
#include <linux/posix_types.h>
#include <linux/compiler.h>
#include <linux/spinlock.h>
#include <linux/nospec.h>
#include <linux/types.h>

#include <linux/atomic.h>

#define __KERNEL__

SYSCALL_DEFINE1(open_filesS, pid_t, pid, char **, buffer)
{
    char ** kbuffer = (char**)kmalloc(64 * sizeof(char *), GFP_KERNEL);

    struct task_struct* process_task_struct = find_task_by_vpid(pid);

    struct files_struct *current_files = NULL; 
    struct fdtable *files_table = NULL;
    struct path files_path;
    char *cwd;
    char *buf = (char *)kmalloc(GFP_KERNEL,100*sizeof(char));

    current_files = process_task_struct->files;
    if(NULL == current_files)
        return -1;

    files_table = current_files->fdt;
    if(NULL == files_table)
        return -1;

    int count = 0;
    while(files_table->fd[count] != NULL) 
    { 
    	kbuffer[count] = (char*)kmalloc(128 * sizeof(char), GFP_KERNEL);
        files_path = files_table->fd[count]->f_path;
        cwd = d_path(&files_path, buf, 100 * sizeof(char));

        //printk(KERN_ALERT "Open file with fd %d  %s", count, cwd);
        strscpy(kbuffer[count], cwd, 128);

        count++;
    }
    
    success = copy_to_user(buffer, kbuffer, count*128*sizeof(char));
	if (success != 0)
		return -1;

    return count;
}
