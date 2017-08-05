// miscdrv_template.c
// 

#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/fcntl.h>
#include <linux/interrupt.h>
#include <linux/spinlock.h>
#include <linux/proc_fs.h>

#include <asm/io.h>
#include <asm/system.h>
#include <asm/unistd.h>
#include <asm/semaphore.h>
#include <asm/uaccess.h>
#include <linux/delay.h>

#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/kernel.h>

#include "miscdrv_template.h"

static struct semaphore     ioctl_semlock; /* lock */  

static void rtc_init(void){
  // add code
  return;
}

static void rtc_deinit(void){
  // add code
  return;
}

static void rtc_get(rtcdate_t * rtcdata){
  // add code
  return;
}

static void rtc_set(rtcdate_t * rtcdata){
  // add code
  return;
}

static int 
miscdrv_template_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg){
  int retval = 0;
    
  down( &ioctl_semlock );

  switch(cmd){
    case RTC_GETTIME:
      rtcdate_t rtcdata;
      rtc_get(&rtcdate);
      if(copy_to_user((rtcdate_t *)arg, &rtcdate,sizeof(rtcdata)) < 0){
        printk(KERN_INFO "%s(%d) RTC_GETTIME copy_to_user failed\r\n", __FUNCTION__, __LINE__);
        return -EFAULT;       
      }
      break;

    case RTC_SETTIME:
      rtcdate_t rtcdata;
      if( copy_from_user((char*)&rtcdata, (char*)arg, sizeof(rtcdata)) < 0){
        printk(KERN_INFO "%s(%d) RTC_SETTIME copy_to_user failed\r\n", __FUNCTION__, __LINE__);
        return -EFAULT;
      }
      rtc_set(&rtcdate);
      break;
    
    default:
      printk(KERN_INFO "%s(%d) ERROR!! unknown cmd: %d\n", __FUNCTION__, __LINE__, cmd);
      retval = -1;
  }

  up( &ioctl_semlock );

  return retval;
}

struct file_operations miscdrv_template_fops = {
  owner:    THIS_MODULE,
  // read:     miscdrv_template_read,
  // write:    miscdrv_template_write,
  ioctl:    miscdrv_template_ioctl,
  // fasync:   miscdrv_template_fasync,
  // flush:    miscdrv_template_flush,
  // open:     miscdrv_template_open,
  // release:  miscdrv_template_release
};

static struct miscdevice miscdrv_template_dev = {
  minor:  MISC_DYNAMIC_MINOR,
  name:   "miscdrv_template",
  fops:   &miscdrv_template_fops,
};

static int __init thisdrv_init(void){
  unsigned int val1;
  rtcdate_t rtcdate;
  int ret;

  printk(KERN_INFO "RTC initialized.\n\r");
  rtc_init();

  ret = misc_register(&miscdrv_template_dev);

	printk(KERN_INFO "%s(%d) complete!!\r\n", __FUNCTION__, __LINE__); 
  return 0;
}

static void __exit thisdrv_exit(void){
  rtc_deinit();
  printk(KERN_INFO "%s(%d) complete!!\r\n", __FUNCTION__, __LINE__);
  return;
}

module_init(thisdrv_init);
module_exit(thisdrv_exit);

MODULE_AUTHOR("Napat Rungruangbangchan");
MODULE_DESCRIPTION("MISCDRV_TEMPLATE");
MODULE_SUPPORTED_DEVICE("AC49x");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");
