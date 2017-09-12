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

#define procfs_name 		"procrw_buffer1k"
#define DATBUF_MAXSIZE		(1024+1)			// 1k with guardian for string data,, binary data can remove guardian 

static char datbufnow[DATBUF_MAXSIZE];
static unsigned long datbufnow_len = 0;

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
		memcpy(buffer, datbufnow, datbufnow_len);
		ret = datbufnow_len;
	}

	return ret;
}

static int 
procfile_write(struct file *file, const char *buffer, unsigned long count, void *data){
	
	/* get buffer length can buffered */
	datbufnow_len = count;
	if (datbufnow_len > (DATBUF_MAXSIZE - 1) ) {
		datbufnow_len = (DATBUF_MAXSIZE - 1);
	}	
	
	/* write data to the buffer */
	if ( copy_from_user(datbufnow, buffer, datbufnow_len) ) {
		printk(KERN_ALERT "ERROR: Could not copy_from_user at %s(%d)\n", __FUNCTION__, __LINE__);  
		return -EFAULT;
	}
	datbufnow[datbufnow_len] = 0;	// guardian

	printk(KERN_INFO "Buffering new data length: %ld\n", datbufnow_len);
	printk(KERN_INFO "\t Try print string dat: %s\n", datbufnow);

	return datbufnow_len;
}

static int 
procfile_remove(void){
	remove_proc_entry(procfs_name, &proc_root);
	printk(KERN_INFO "/proc/%s is removed\n", procfs_name);  
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
	devproc_entry->write_proc 	= procfile_write;
	devproc_entry->owner 	 	= THIS_MODULE;
	devproc_entry->mode 	 	= S_IFREG | S_IRUGO; //| S_IWUGO;
	devproc_entry->uid 	 		= 0;
	devproc_entry->gid 	 		= 0;
	devproc_entry->size 	 	= 37;

	printk(KERN_INFO "/proc/%s is created\n", procfs_name);	
	return 0;	/* everything is ok */
}

static int __init 
testdrv_init(void){

	procfile_create();

	printk(KERN_INFO "%s(%d) complete!!\n", __FUNCTION__, __LINE__);
	return 0;
}

static void __exit 
testdrv_exit(void){

	procfile_remove();

	printk(KERN_INFO "%s(%d) complete!!\n", __FUNCTION__, __LINE__);
  	return;
}

module_init(testdrv_init);
module_exit(testdrv_exit);

MODULE_AUTHOR("Napat Rungruangbangchan");
MODULE_DESCRIPTION("PROC READ SAMPLE");
MODULE_SUPPORTED_DEVICE("AC49x");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");
