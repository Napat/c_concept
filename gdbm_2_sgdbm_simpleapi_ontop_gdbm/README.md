  
Note: See `ubuntu_workaround.md` for gdbm requirements package.


```
$ make
$ ./a.out
Example
 ./binary insert hashkey1 1 firstname lastname city 1986
 ./binary update key1 2 fname lname city 1987
 ./binary delete key1
 ./binary show key1
$
$ ./a.out insert key1 1 f1 l1 bbk 1986
Insert key key1 complete!!
$
$ ./a.out show key1
KEY: key1
         id: 1
         firstname: f1
         lastname: l1
         city: bbk
         yearofbirth: 1986

$ ./a.out update key1 1 f01 l01 bbk 1987
Update key key1 complete!!
$ 
$  ./a.out show key1
KEY: key1
         id: 1
         firstname: f01
         lastname: l01
         city: bbk
         yearofbirth: 1987

$ 
$  ./a.out update key2 2 f02 l02 bbk 1988
Update key key2 complete!!
$ ./a.out update key3 3 f03 l03 au 1989
Update key key3 complete!!
$  ./a.out insert key3 3 f03 l03 au 1989
sgdbm_insert(53) insert error, expect key 'key3' is already in database
$  ./a.out delete key3
$  ./a.out insert key3 3 f03 l03 au 1989
Insert key key3 complete!!
$
```
