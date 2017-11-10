
# Shared library(.so)  
ออปชั่นที่จำเป็นในขั้นตอนการสร้าง dynamic lib(.so) ขึ้นมามีสองอันคือ `-fPIC` และ `-shared` ซึ่งมีรายละเอียดดังนี้  
  
The `-fPIC` flag stands for “Position Independent Code” generation, a requirement for shared libraries. Because it’s impossible to know where the shared library code will be, this flag allows the code to be located at any virtual address at runtime.  
  
The `-shared` flag creates the shared library (shared libraries have the prefix lib and suffix .so [for shared object].  

# Workflow
1.การสร้าง dynamic library .so ขึ้นมา สามารถดูรายละเอียดได้ใน `lib/libsystemcall/`  

```
$ make libs
$ ls output/lib/*.so
output/lib/libsystemcall.so
$
$ ldd output/lib/libsystemcall.so
        linux-vdso.so.1 =>  (0x00007fffc7799000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f54841e0000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f5484800000)
$         
$ nm output/lib/libsystemcall.so
                 U access@@GLIBC_2.2.5
0000000000201068 B __bss_start
                 U closedir@@GLIBC_2.2.5
0000000000201068 b completed.6973
                 w __cxa_finalize@@GLIBC_2.2.5
0000000000000850 t deregister_tm_clones
00000000000008c0 t __do_global_dtors_aux
0000000000200e08 t __do_global_dtors_aux_fini_array_entry
0000000000201060 d __dso_handle
0000000000200e18 d _DYNAMIC
0000000000201068 D _edata
0000000000201070 B _end
                 U __errno_location@@GLIBC_2.2.5
0000000000000c20 T _fini
0000000000000900 t frame_dummy
0000000000200e00 t __frame_dummy_init_array_entry
0000000000000d38 r __FRAME_END__
0000000000201000 d _GLOBAL_OFFSET_TABLE_
                 w __gmon_start__
0000000000000788 T _init
0000000000000bc2 T isAccessDir
0000000000000b92 T isAccessFile
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
0000000000200e10 d __JCR_END__
0000000000200e10 d __JCR_LIST__
                 w _Jv_RegisterClasses
                 U opendir@@GLIBC_2.2.5
0000000000000880 t register_tm_clones
                 U __stack_chk_fail@@GLIBC_2.4
                 U system@@GLIBC_2.2.5
0000000000000935 T system_printf
0000000000000a52 T system_sync_printf
0000000000201068 d __TMC_END__
                 U vsprintf@@GLIBC_2.2.5
$ 
```

2.คอมไพล์ไฟล์ binary ที่เชื่อมต่อ(linked) กับ library .so  
```
$ make app_linked_dynamic_so
$ make output
$ ls output/app_linked_dynamic_so
output/app_linked_dynamic_so
$
```

Note: โปรเจคนี้สามารถสั่ง make ทั้งสองขั้นตอนได้ด้วยคำสั่งเดียวดังนี้
```
$ make
$ ls output/lib/*.so
output/lib/libsystemcall.so
$ ls output/app_linked_dynamic_so
output/app_linked_dynamic_so
$
```


3. ในขั้นตอนการรันโปรแกรมจำเป็นจะต้องตั้งค่าให้ linux มองเห็นไฟล์ .so ด้วย สามารถทำได้หลายวิธีดังนี้   
3.1 นำไฟล์ .so ไปวางไว้ที่ library path ที่ linux รู้จักอยู่แล้วเช่น /lib  
3.2 ตั้งค่าที่เก็บไฟล์ .so ไว้ลงในตัวแปล `LD_LIBRARY_PATH` และทำการ export path  
หากใครจะใช้วิธีแรกก็แค่ copy ไฟล์ลงไปยังตำแหน่งที่ต้องการ ในที่นี้จึงจะแสดงวิธีการที่ 3.2 คือจะเข้าไปใน ไดเร็คทอรี่ output และ export path อ้างอิงไปยังที่เก็บไฟล์ .so เอาไว้ `${PWD}/lib`  

```
$ cd output 
$ ldd app_linked_dynamic_so
        linux-vdso.so.1 =>  (0x00007ffff6127000)
        libsystemcall.so => not found
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f78da9b0000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f78dae00000)
$        
$ export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${PWD}/lib
$ echo $LD_LIBRARY_PATH
:<workdir>/c_concept/sharelibs/dynamiclibrary_so/output/lib
$
$ ldd app_linked_dynamic_so
        linux-vdso.so.1 =>  (0x00007ffff75cd000)
        libsystemcall.so => /mnt/d/workdir/c_concept/sharelibs/dynamiclibrary_so/output/lib/libsystemcall.so (0x00007ff7b8e30000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007ff7b8a60000)
        /lib64/ld-linux-x86-64.so.2 (0x00007ff7b9200000)
$         
$ ./app_linked_dynamic_so
total 16
drwxrwxrwx 0 root root 4096 Nov 14 00:10 .
drwxrwxrwx 0 root root 4096 Nov 14 00:10 ..
-rwxrwxrwx 1 root root 8602 Nov 14 00:10 app_linked_dynamic_so
drwxrwxrwx 0 root root 4096 Nov 14 00:10 lib
-rwxrwxrwx 1 root root 1792 Nov 14 00:10 main.o
------------------------------------
4096 .
4096 ..
8602 app_linked_dynamic_so
4096 lib
1792 main.o
------------------------------------
$
$
$ nm app_linked_dynamic_so
0000000000601040 B __bss_start
0000000000601040 b completed.6973
0000000000601030 D __data_start
0000000000601030 W data_start
00000000004005e0 t deregister_tm_clones
0000000000400650 t __do_global_dtors_aux
0000000000600e08 t __do_global_dtors_aux_fini_array_entry
0000000000601038 D __dso_handle
0000000000600e18 d _DYNAMIC
0000000000601040 D _edata
0000000000601048 B _end
0000000000400744 T _fini
0000000000400670 t frame_dummy
0000000000600e00 t __frame_dummy_init_array_entry
0000000000400880 r __FRAME_END__
0000000000601000 d _GLOBAL_OFFSET_TABLE_
                 w __gmon_start__
0000000000400550 T _init
0000000000600e08 t __init_array_end
0000000000600e00 t __init_array_start
0000000000400750 R _IO_stdin_used
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
0000000000600e10 d __JCR_END__
0000000000600e10 d __JCR_LIST__
                 w _Jv_RegisterClasses
0000000000400740 T __libc_csu_fini
00000000004006d0 T __libc_csu_init
                 U __libc_start_main@@GLIBC_2.2.5
000000000040069d T main
0000000000400610 t register_tm_clones
00000000004005b0 T _start
                 U system_printf
0000000000601040 D __TMC_END__
$
$
```
  
