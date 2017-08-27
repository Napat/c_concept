
# Detecting memory leaks 
สำหรับการตรวจสอบว่าเกิดปัญหา memory leaks รึเปล่าเราสามารถทำได้หลายวิธีเช่น [ใช้ vagrind ](http://bl0rg.krunch.be/memleak-pthreads.html) ช่วยตรวจสอบในระดับ memory หรืออาจจะเลือกใช้วิธีตรวจสอบเบื้องต้นง่ายๆได้โดยไม่ต้องเข้าไปยุ่งเกี่ยวกับ source code หรือโปรแกรมยุ่งยากได้ด้วยหลักการดังนี้  
1. นับจำนวน Thread stacks ใน process นั้นๆี่ถูก map อยู่ด้วยคำส่ัง pmap ซึ่งจะได้ค่าผลรวมของ running active thread และ terminated thread ที่ exit ไปแล้วแต่ยังมีการจองหน่วยความจำ (map memory) ดังนี้  
`pmap PID | grep 8192K | wc -l`  
  
Note: ตัวเลข 8192K อาจจะต้องปรับเปลี่ยนไปตาม platform หรือ distrol ที่ใช้งานเช่น 10240KB บน Redhat server release 5.4  
  
2. นับเฉพาะจำนวน active running threads ใน process นั้นๆด้วยคำสั่ง  
`ls /proc/PID/task | wc -l`  
  
3. นำตัวเลขทั้งสองมาพิจารณาก็จะได้ค่า running active thread และ terminated thread ที่ยังไม่ถูก free เมื่อรันโปรแกรมไปซักระยะแล้วถ้าค่าตัวเลขทั้งสองมีแนวโน้มกระจายตัวออกห่างกันไปเรื่อยๆโดยที่จำนวน terminated thread  ที่ยังไม่ถูก free มีค่าคงเหลือมากกว่า running active thread ซะอีกก็แสดงว่าเกิด memory leaks ขึ้นแล้วนั่นเอง 
  
```
$ make
$ cd output 
$ ./pthread_memleaks > /dev/null &
[1]  1036
$
$ ls /proc/1036/task | wc -l
2
$ ls /proc/1036/task | wc -l
1
$ ls /proc/1036/task | wc -l
1
$ ls /proc/1036/task | wc -l
2
$ ls /proc/1036/task | wc -l
1
$
$ pmap 1036 | grep 8192K | wc -l
10
$ pmap 1036 | grep 8192K | wc -l
11
$ pmap 1036 | grep 8192K | wc -l
12
pmap 1036 | grep 8192K | wc -l
22
$
$ ls /proc/1036/task | wc -l
2
$ ls /proc/1036/task | wc -l
1
$ ls /proc/1036/task | wc -l
1
$
```


