
# Manual pages: man
Linux comes with great useful documentation by using `man` you can access a tones of manual pages.  
Manual pages isn't always well organized then sometimes may also be out-of-date, so if the system doesn't behave the way a man page says it should, it may be the man page is outdated but still powerful to used.   

The man pages are divided into numbered sections, the most important are these:  
1. User commands  
2. System commands  
3. Standard library functions  
8. System/Administrative commands  
  
Basically to look up a man page of `nameOfSomething`, just simply invoke  
```
$ man nameOfSomething
```

In some cases the same name of something occurs then thay are divied into more than on section; you can specify the section explicitly by placeing the section number before the name. For example, if you want to get the man page of `sleep` **command**, you can use:  
`$ man sleep`
or   
`$ man 1 sleep`  

But if you want to see the man page of `sleep` **library** to write the source code, just use this command:  
`$ man 3 sleep`  
  
If you're not sure which sections you want, you can display one-line summary of all sections by using command `whatis`, for example:
```
$ whatis sleep
sleep (1)            - delay for a specified amount of time
sleep (3)            - sleep for the specified number of seconds
$
```
  
You also can perform a keyword search on the summary lines by using `man -k keyword`, something like:  
  
```
man -k delay
kbdrate (8)          - reset the keyboard repeat rate and delay time
pam_faildelay (8)    - Change the delay on failure per-application
sleep (1)            - delay for a specified amount of time
tc-codel (8)         - Controlled-Delay Active Queue Management algorithm
tc-fq_codel (8)      - Fair Queuing (FQ) with Controlled Delay (CoDel)
```
  

# Info  
The `info` documentation system contains more detailed for many components of the GNU/ Linux system than manual pages. In several programs, info pages are hypertet documents similar to Web pages. To see `info`  document just type `info`, for example:  
```
$ info gcc
$ info libc
$ info gdb
$ info emacs 
$ info info
```

# Program exit codes
When a program ends it indicates its status with an exit code; by convention , an eit code of zero denotes successful execution, while nonzero exit codes indicates the error occurred.  
With most shells, to iibtain the exit code of the most recently ended program using the speical `$?`:
```
$ ls /
$ echo $?
0
$ ls /xxx
ls: cannot access /xxx: No such file or directory
$ echo $?
2
$
```