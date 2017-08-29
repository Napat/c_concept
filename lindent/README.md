
```
$ cat test.c
#include <stdio.h>

//test1
// test2



/********************************
  Multiline comment
****************************/

void test()
{
printf("%s()\r\n", __FUNCTION__);
}

int main()
{
printf("hahaha\r\n");
 test();
   return 0;

}
$ 
$ 
$ 
$ 
$ make
./Lindent test.c -o test_ready.c
diff -u test.c test_ready.c; [ $? -lt 2 ]
--- test.c      2017-04-13 23:20:18.068774900 +0700
+++ test_ready.c        2017-08-29 16:11:18.176694800 +0700
@@ -3,21 +3,19 @@
 //test1
 // test2

-
-
 /********************************
   Multiline comment
 ****************************/

 void test()
 {
-printf("%s()\r\n", __FUNCTION__);
+       printf("%s()\r\n", __FUNCTION__);
 }

 int main()
 {
-printf("hahaha\r\n");
- test();
-   return 0;
+       printf("hahaha\r\n");
+       test();
+       return 0;

 }
gcc test_ready.c -o testapp
$ 
$
$
$ cat test_ready.c
#include <stdio.h>

//test1
// test2

/********************************
  Multiline comment
****************************/

void test()
{
        printf("%s()\r\n", __FUNCTION__);
}

int main()
{
        printf("hahaha\r\n");
        test();
        return 0;

}
$ 
$ 
$ 
$ 
```


