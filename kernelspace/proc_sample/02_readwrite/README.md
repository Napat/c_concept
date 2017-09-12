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
$ insmod proc_rw.ko 
/proc/procrw_buffer1k is created
testdrv_init(97) complete!!
$
$
$ echo 1234567890 > /proc/procrw_buffer1k 
Buffering new data length: 11
     Try print string dat: 1234567890

$ 
$ 
$ cat /proc/procrw_buffer1k 
1234567890
$
$ cat /proc/procrw_buffer1k 
1234567890
$
$ echo 12345 > /proc/procrw_buffer1k 
Buffering new data length: 6
     Try print string dat: 12345

$
$
$ cat /proc/procrw_buffer1k 
12345
$
$
$ rmmod proc_read.ko 
/proc/procrw_buffer1k is removed
testdrv_exit(106) complete!!
$
```



