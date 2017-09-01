More: https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html  
  
**GCC (the "Gnu Compiler Collection") also defines __FUNCTION__ and __PRETTY_FUNCTION__. These are both the same as __func__ for C. For C++, __PRETTY_FUNCTION__ is something different.**
  
  
```
$ make
$ cd output
$ ./stdmacro_example
main(24) file name: main.c
main(25) compile date: Sep  1 2017
main(26) compile time: 19:35:08
myprinter(13)
myprinter(17)
myprinter(18)
```
  
