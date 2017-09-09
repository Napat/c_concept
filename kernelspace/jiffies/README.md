jiffies: the global kernel variable holds the number of linux timer interrupt ticks since the system booted.  
  
HZ holds number of timer interrupt in a second.  
Common value of HZ is 1000(config define when kernel setup or <kernel>/include/sam-generic)  

systemUptime(seconds) = jiffies / HZ  
```
$ uptime
14:47:29 up 30 min,  0 users,  load average: 0.52, 0.58, 0.59
```

unsigned long time_stamp = jiffies;  // now
unsigned long next_tick = jiffies + _1;  // one tick from now
unsigned long next5sec = jiffies + 5*HZ; // five seconds from now


# kernel module jiffies_sample.c
```
$ make
$ insmod jiffies_sample.ko
Value of jiffies is 8669528
$ dmesg | tail -n 1
Value of jiffies is 8669528
$ rmmod jiffies_sample.ko
```

