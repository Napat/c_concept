# เกริ่นนำ  
ในการใช้งาน POSIX threads(pthreads) นั้นความเข้าใจในเรื่อง joinable threads และ detached threads มีความสำคัญและจำเป็นที่จะต้องทำความเข้าใจให้ดีไม่เช่นนั้นจะนำไปสู่ปัญหา memory leaks ในตอนใช้งานจริงได้  
  
# Joinable threads  
โดย default attribute ของ POSIX threads แล้ว เมื่อเราสร้างเทรดขึ้นมาใหม่จะได้เทรดที่เป็น joinable threads ซึ่งระบบจะมีการ allocates private storage ขึ้นมาเพื่อใช้ในการเก็บค่าต่างๆเช่น exit status ซึ่งจะยังคงอยู่หลังจากเทรดนั้นถูกทำลาย(ทำงานเสร็จสิ้น)เพื่อส่งคืนค่าไปยังผู้เรียก pthread_join() ดังตัวอย่างก่อนหน้านี้ หลังจากนั้น pthread_join() จะช่วยทำการ free memory ในส่วนดังกล่าวให้โดยอัตโนมัติเพื่อคืนทรัพยากรให้กับระบบเพื่อนำไปใช้ใหม่(recycled)  

ดังนั้นหากเราสร้าง joinable thread ขึ้นมาโดยไม่ได้ใช้งานคู่กับการ join ก็จะทำให้เกิดปัญหา memory leaks ขึ้นมาทันที  

# Detached threads 
เมื่อเทรดถูกตั้งค่าให้เป็น detached threads แล้ว หากเทรดถูกทำลาย(terminates) ระบบจะทำการคืนทรัพยากรทุกอย่างกลับให้โดยอัตโนมัติ ซึ่งมีประโยชน์อย่างมากเนื่องจากในการพัฒนาโปรแกรมขึ้นมาในหลายๆครั้งเราแค่ต้องการสร้างเทรดขึ้นมาเพื่อมอบหมายงานให้ไปทำโดยที่เราไม่ได้จำเป็นจะต้องสนใจว่าเทรดดังกล่าวจะทำงานเสร็จสิ้นเมื่อไหร่หรือมีค่า return status เป็นอย่างไร ในกรณีแบบนี้การตั้งค่าให้เทรดทำงานแบบ detached threads จะมีความเหมาะสมและสะดวกมากกว่า joinable threads  
Note: เทรดที่ทำงานแบบ detached threads จะไม่สามารถใช้งานร่วมกับ pthread_join()เพื่อตรวจสอบค่าสถานะของเทรดได้นะ  
  
```
$ make
$ cd output 
$ ./pthread_detach
counter=0
Create new printer context
output from printer1 round 0
output from printer1 round 1
counter=1
output from printer1 round 2
output from printer1 round 3
counter=2
output from printer1 round 4
output from printer1 round 5
counter=3
output from printer1 round 6
output from printer1 round 7
counter=4
output from printer1 round 8
output from printer1 round 9
counter=5
counter=6
counter=7
counter=8
counter=9
counter=10
Create new printer context
output from printer1 round 0
output from printer1 round 1
counter=11
output from printer1 round 2
output from printer1 round 3
counter=12
output from printer1 round 4
output from printer1 round 5
counter=13
output from printer1 round 6
output from printer1 round 7
counter=14
output from printer1 round 8
output from printer1 round 9
counter=15
counter=16
counter=17

```


