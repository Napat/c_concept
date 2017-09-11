/**
 * @file miscdrv_template.c
 * @author Napat Rungruangbangchan
 * @date 9 September 2017 
 * @brief About jiffies, HZ, timer
 * @Compiler: 
 * @License: 
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

#define procfs_name "procread_info"

static int
procfile_read(char *buffer,
	      char **buffer_location,
	      off_t offset, int buffer_length, int *eof, void *data){
	int ret;
	
	*eof = 1;
	if (offset > 0) {
		/* we have finished to read, return 0 */
		ret  = 0;
	} else {
		/* fill the buffer, return the buffer size */
		ret = sprintf(buffer, "Value of jiffies is %lu\n", jiffies);
	}

	return ret;
}

static int 
procfile_remove(void){
	remove_proc_entry(procfs_name, &proc_root);
	printk(KERN_INFO "/proc/%s removed\n", procfs_name);  
}

static int 
procfile_create(void){
	struct proc_dir_entry *devproc_entry;

	devproc_entry = create_proc_entry(procfs_name, 0644, NULL);
	if (devproc_entry == NULL) {
		remove_proc_entry(procfs_name, &proc_root);
		printk(KERN_ALERT "Error: Could not initialize /proc/%s\n", procfs_name);
		return -ENOMEM;
	}

	devproc_entry->read_proc 	= procfile_read;
	devproc_entry->owner 	 	= THIS_MODULE;
	devproc_entry->mode 	 	= S_IFREG | S_IRUGO;	// | S_IWUGO
	devproc_entry->uid 	 		= 0;
	devproc_entry->gid 	 		= 0;
	devproc_entry->size 	 	= 37;

	printk(KERN_INFO "/proc/%s created\n", procfs_name);	
	return 0;	/* everything is ok */
}

static int __init 
drv_init(void){

	procfile_create();

	printk(KERN_INFO "%s(%d) complete!!\r\n", __FUNCTION__, __LINE__);
	return 0;
}

static void __exit 
drv_exit(void){

	procfile_remove();

	printk(KERN_INFO "%s(%d) complete!!\r\n", __FUNCTION__, __LINE__);
  	return;
}

module_init(drv_init);
module_exit(drv_exit);

MODULE_AUTHOR("Napat Rungruangbangchan");
MODULE_DESCRIPTION("PROC READ SAMPLE");
MODULE_SUPPORTED_DEVICE("AC49x");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");
