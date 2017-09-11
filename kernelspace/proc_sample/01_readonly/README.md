Good /proc File System topics: http://tldp.org/LDP/lkmpg/2.6/html/c708.html

# Basic manual make kernel module(only oneline in Makefile is used `obj-m += xxx.o`)  
```
$ make -C <your_kernel_path> M=`pwd` modules
$ ls *.ko
proc_sample.ko
$
```

# Make kernel module using more Makefile ability (more info: cat Makefile)
```
$ make clean
$ make
$ ls *.ko
proc_sample.ko
$
```

# Test driver module
```
$ insmod proc_read.ko 
/proc/procread_info created
drv_init(68) complete!!
$
$ cat /proc/procread_info 
Value of jiffies is 8768467
$ 
$ cat /proc/procread_info 
Value of jiffies is 8769729
$
$ cat /proc/procread_info 
Value of jiffies is 8770081
$
$ rmmod proc_read.ko 
/proc/procread_info removed
drv_exit(77) complete!!
$
```

