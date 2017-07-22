  
Note: See `ubuntu_workaround.md` for requirements package.


```
$ make
$./a.out
---------------------
main(134) dat1=Hello World!!
main(135) dat2 fullname is 'Uzumaki Naruto'
---------------------
main(154) dat1=World!!
---------------------
$
$ ./a.out
---------------------
main(125) insert error, expect key 'msg1' is available in database
main(134) dat1=World!!
main(135) dat2 fullname is 'Uzumaki Naruto'
---------------------
main(154) dat1=World!!
---------------------
$
$ rm db01.gdbm
$ ./a.out
---------------------
main(134) dat1=Hello World!!
main(135) dat2 fullname is 'Uzumaki Naruto'
---------------------
main(154) dat1=World!!
---------------------
```
