Library คือข้อมูล object files ที่เก็บข้อมูลฟังก์ชันและตัวแปรต่างๆเพื่อสะดวกในการเรียกใช้งานหรือเพื่อความสะดวกในการแจกจ่ายโปรแกรมหรือฟังก์ชั่นการทำงานต่างๆ  
บน linux os นั้นชื่อของ library จะขึ้นต้นด้วยคำว่า lib เช่น libc.so เป็นต้น ในภาษา C สามารถแบ่ง libraries ออกเป็น 2 ประเภทใหญ่ๆ ดังนี้  
  
1. System libraries คือ library ที่มากับระบบหรือ toolchain ตั้งแต่ต้นอยู่แล้ว สามารถเรียกใช้งานได้ทันทีเพียงแค่เรียก include เข้ามาในโปรแกรม เช่น  
```
#include <stdio.h>          // using libc
#include <math.h>           // using libm
#include <ncurses.h>        // using libcurses
```
  
2. Userdefine libraries คือ library ที่ผู้ใช้งานสร้างขึ้นมาใหม่ สามารถแบ่งออกเป็นประเภทย่อยๆได้ดังนี้  
2.1 static library(.a) คือ archive file ซึ่งได้มาจาก object files(.o) 
2.2 shared library(.so) คือ ไฟล์ object code ซึ่งถูกจัดเก็บแบบ independence position เพื่อความสามารถในการเรียกใช้งานในขั้นตอนรันโปรแกรมโดยไม่จำเป็นจะต้องรวมเข้ากับโปรแกรมหลักได้  
2.3 converience library คือการสร้างการจัดการไฟล์ libraries หลายๆไฟล์และติดตั้งแบบมีขั้นขั้นตอนแบบแผน ใช้งานในกรณีที่ libraries มีความซับซ้อน    
  
  