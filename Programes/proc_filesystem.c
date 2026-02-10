/*       
	 \\\
         ~~~
	|^_^|
       /|___|\
     (*)|   |(*) 
       _|_ _|_
       |_| |_|
	
       This simple module create proc file called \"eg_proc_file\" and defining read and write
       function for proc file. this program to just demonstrate the proc file system and showcas
       data exchange between user space program and kernel space.
*/

#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/proc_fs.h>
#include<linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Mouse Driver");

#define procfs_name "eg_proc_file"
unsigned char msg[30] = "Hello proc read successfully\n";
static struct proc_dir_entry* our_proc_file;
static char procfs_buffer[1024];
int procfs_buffer_size;	
int count = 0;

static ssize_t read_proc(struct file *file_ptr, char __user *buffer, size_t buffer_len, loff_t *offset){

			if(copy_to_user(buffer, msg, 30)){
				pr_info("Proc : failed to copy to user\n");
				return 0;
			}
			if(count == 1){
				count = 0;
				return 0;
			}
			count++;
			return 30;

}

static ssize_t write_proc(struct file *file, const char __user *buff, size_t len, loff_t *off){

	procfs_buffer_size = len;
	if (procfs_buffer_size > 1024)
		procfs_buffer_size = 1024;

	if (copy_from_user(procfs_buffer, buff, procfs_buffer_size)){
		pr_info("Proc : failed to write");
		return -EFAULT;
	}

	procfs_buffer[procfs_buffer_size] = '\0';
	*off += procfs_buffer_size;
	pr_info("Proc : Hey proc write successfully\n");

	return procfs_buffer_size;

}

struct proc_ops proc_file_fops = {
	.proc_read = read_proc,
	.proc_write = write_proc
};

static int __init driver_init(void){
	
	// register the proc file
	our_proc_file = proc_create(procfs_name, 0444, NULL, &proc_file_fops);
	
	if (our_proc_file != NULL) {
		pr_info("Proc : proc file created /proc/%s\n", procfs_name);
		return 0;
	}
	else{
		pr_info("Proc : Failed to create proc file\n");
		return -ENOMEM;
	}
		
}

static void __exit driver_exit(void){
	// de-register the proc file
	proc_remove(our_proc_file);
	pr_info("Proc : proc file removed\n");
}

module_init(driver_init);
module_exit(driver_exit);
