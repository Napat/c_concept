/**
 * @file chardrv_template.c
 * @author Napat Rungruangbangchan
 * @date 14 Aguent 2017 
 * @brief This file is part of char driver sample
 * @Compiler: 
 * @License: 
 */

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

#include <linux/chardevice.h>
#include <linux/fs.h>
#include <linux/kernel.h>

#include "chardrv_template.h"

static int    major_num = RTC_DRV_MAJOR, minor_num = RTC_DRV_MINOR;
static struct cdev rtc_cdev;
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
chardrv_template_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg){
  int retval = 0;
  rtcdev_arg_t header;
  rtcdate_t rtcdata;

  down( &ioctl_semlock );
  copy_from_user(&header, (rtcdev_arg_t *)arg , sizeof(header));

  switch(cmd){
    case RTC_GETTIME:
      rtc_get(&rtcdate);
      header.iserr = 0;   // no error
      if(copy_to_user(header.api_arg , &rtcdate, sizeof(rtcdate)) < 0){
        printk(KERN_ERR "%s(%d) RTC_GETTIME copy_to_user failed\r\n", __FUNCTION__, __LINE__);
        header.iserr = 1;
        return -EFAULT;       
      }
      break;

    case RTC_SETTIME:
      if( copy_from_user(&rtcdate, header.api_arg , sizeof(rtcdate))  < 0){
        printk(KERN_ERR "%s(%d) RTC_SETTIME copy_to_user failed\r\n", __FUNCTION__, __LINE__);
        header.iserr = 1;
        return -EFAULT;
      }
      rtc_set(&rtcdate);
      break;
    
    default:
      printk(KERN_ERR "%s(%d) ERROR!! unknown cmd: %d\n", __FUNCTION__, __LINE__, cmd);
      retval = -1;
  }

  // Send header to user
  copy_to_user(&arg ,&header, sizeof(header));

  up( &ioctl_semlock );

  return retval;
}

struct file_operations chardrv_template_fops = {
  owner:    THIS_MODULE,
  // read:     chardrv_template_read,
  // write:    chardrv_template_write,
  ioctl:    chardrv_template_ioctl,
  // fasync:   chardrv_template_fasync,
  // flush:    chardrv_template_flush,
  // open:     chardrv_template_open,
  // release:  chardrv_template_release
};

static int __init thisdrv_init(void){
  unsigned int val1;
  rtcdate_t rtcdate;
  int ret;

  printk(KERN_INFO "RTC initialized.\n\r");

  // init feature
  rtc_init();

  // init driver 
  sema_init(&ioctl_semlock, 1);
  //ret = register_chrdev(major_num, NODENAME, &chardrv_template_fops);
  dev_id = MKDEV(major_num, minor_num);
  ret = register_chrdev_region(dev_id, 1, NODENAME);
  if(ret < 0){ 
    printk(KERN_ERR "%s(%d) Unable to register dev with ret %d\n", __FUNCTION__, __LINE__, ret);
    return -ENOMEM;
  }
  // &rtc_cdev = cdev_alloc();
  cdev_init(&rtc_cdev, &rtc49x_fops);
  cdev_add(&rtc_cdev, dev_id, 1);

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
MODULE_DESCRIPTION("CHARDRV_TEMPLATE");
MODULE_SUPPORTED_DEVICE("AC49x");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");
