    
# Static library(.a)  
Static libraries(.a) ทำงานได้เร็วกว่า shared(dynamic) libraries(.so) เพราะเป็นการนำเอาข้อมูลไลบรารี่ที่ต้องการใช้งานรวมเข้ากับ executable file เลย 
แต่ก็มีข้อด้อยกว่าในเรื่องของขนาดพื้นที่เก็บข้อมูลเช่นในกรณีที่ต้องการนำ library ดังกล่าวไปใช้กับ executable files หลายๆโปรแกรมซึ่งโปรแกรมหนึ่งๆจะมีโค๊ตของ library ดังกล่าวสำเนาอยู่แยกกันไป 
แต่ในกรณีของ dynamic library สามารถใช้งานร่วมกันได้พร้อมๆกันได้
รวมไปถึงหากมีการแก้ไข static library .a แม้เพียงนิดเดียวก็จำเป็นจะคอมไพล์ executable file ที่ต้องการนำไปใช้ใหม่อีกด้วย   
  
## Shortcut Step  
```
$ cd <libfoo>
$ gcc -c *.c *.o 
$ ar -rcv libfoo.a *.o  
$  
$ cd <barapp>
$ gcc -o bar bar.c <libfoo>/libfoo.a
```
  
## Note
```
The -r flag inserts the file members into the archive [liball.a] with replacement. This operation differs from q(without checking for replacement).
The -c flag creates the archive [libfoo.a].
```
  
## make project  
```
$ make
$ cd output
$ ./app_linked_staticlib_a
Wed Sep 13 00:08:06 2017
$
```
  
## More information
```
$ nm app_linked_staticlib_a
00000000006020a0 B __bss_start
                 U clock_gettime@@GLIBC_2.17
00000000006020a0 b completed.6973
                 U ctime@@GLIBC_2.2.5
0000000000602090 D __data_start
0000000000602090 W data_start
0000000000400830 t deregister_tm_clones
00000000004008a0 t __do_global_dtors_aux
0000000000601e18 t __do_global_dtors_aux_fini_array_entry
0000000000602098 D __dso_handle
0000000000601e28 d _DYNAMIC
00000000006020a0 D _edata
00000000006020e8 B _end
                 U __errno_location@@GLIBC_2.2.5
0000000000400ff4 T _fini
00000000004008c0 t frame_dummy
0000000000601e10 t __frame_dummy_init_array_entry
00000000004013f8 r __FRAME_END__
0000000000400c91 T getdelta_time_usec
0000000000400c51 T get_humanreadtime
0000000000400b31 T get_time
0000000000400d9d T getTimeDay
0000000000400dfb T getTimeHour
0000000000400e59 T getTimeMin
0000000000400d3c T getTimeMonth
                 U gettimeofday@@GLIBC_2.2.5
0000000000400eb7 T getTimeSec
0000000000400cd9 T getTimeYear
0000000000400bdd T get_unixtime
0000000000400f15 T getuptime
0000000000602000 d _GLOBAL_OFFSET_TABLE_
                 w __gmon_start__
00000000004006d8 T _init
0000000000601e18 t __init_array_end
0000000000601e10 t __init_array_start
0000000000401000 R _IO_stdin_used
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
0000000000601e20 d __JCR_END__
0000000000601e20 d __JCR_LIST__
                 w _Jv_RegisterClasses
0000000000400ff0 T __libc_csu_fini
0000000000400f80 T __libc_csu_init
                 U __libc_start_main@@GLIBC_2.2.5
                 U localtime@@GLIBC_2.2.5
00000000004008ed T main
                 U mktime@@GLIBC_2.2.5
                 U printf@@GLIBC_2.2.5
0000000000400c19 T print_humanreadtime
0000000000400bb0 T print_unixtime
                 U pthread_mutex_lock@@GLIBC_2.2.5
                 U pthread_mutex_unlock@@GLIBC_2.2.5
0000000000400860 t register_tm_clones
0000000000400929 T set_timeFromBrokenDownTime
0000000000400a1d T set_timeFromBrokenDownTimeFull
                 U settimeofday@@GLIBC_2.2.5
                 U sprintf@@GLIBC_2.2.5
0000000000400800 T _start
                 U strcpy@@GLIBC_2.2.5
                 U time@@GLIBC_2.2.5
00000000006020a0 D __TMC_END__
00000000006020c0 B unixtime_mutex
```
  
  