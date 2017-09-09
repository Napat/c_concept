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


static int __init jiffies_init(void){
  pr_info("Value of jiffies is %lu\n", jiffies);
  return 0;
}

static void __exit jiffies_exit(void){
  printk(KERN_INFO "%s(%d) complete!!\r\n", __FUNCTION__, __LINE__);
  return;
}

module_init(jiffies_init);
module_exit(jiffies_exit);

MODULE_AUTHOR("Napat Rungruangbangchan");
MODULE_DESCRIPTION("JIFFIES");
MODULE_SUPPORTED_DEVICE("AC49x");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");
