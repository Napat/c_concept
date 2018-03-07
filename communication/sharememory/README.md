
# Linux command   
`ipcs -m`: Show ipc share memory information.  
`ipcrm -M <sharmem key id>`: To delete share memory segment.  
  
```
$ make
$ cd output 
$ ./shmem_1 
mainapp_1.c:shm_init_creater Create shared memory with size 10.

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status      
...        
0x000022b8 5996557    napat      666        10         1                       
...      

--------------------
mainapp_1.c(62): temp1=0
mainapp_1.c(63): temp2=0
mainapp_1.c(64): fan1.level=1
mainapp_1.c(65): fan1.rpm=0
mainapp_1.c(66): fan2.level=2
mainapp_1.c(67): fan2.rpm=0
--------------------
mainapp_2.c:shm_init_attacher Attach shared memory with size 10.
mainapp_2.c(45): temp1=0
mainapp_2.c(46): temp2=0
mainapp_2.c(47): fan1.level=1
mainapp_2.c(48): fan1.rpm=0
mainapp_2.c(49): fan2.level=2
mainapp_2.c(50): fan2.rpm=0
--------------------
mainapp_1.c(77): temp1=28
mainapp_1.c(78): temp2=29
mainapp_1.c(79): fan1.level=2
mainapp_1.c(80): fan1.rpm=999
mainapp_1.c(81): fan2.level=3
mainapp_1.c(82): fan2.rpm=1000
--------------------

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status      
...  
*** key 0x000022b8(8888) will be deleted ***   
... 

--------------------

```
  

