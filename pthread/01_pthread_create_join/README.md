
  
การใช้งาน pthread จะต้องมีการใส่ -lpthread เพื่อใช้งาน library pthread ด้วย  
pthread_join จะตรวจสอบและรอจนกว่า thread นั้นๆจะทำงานจนเสร็จ จากนั้นจะทำการคืนค่า(free) memory ที่ thread ใช้งาน ซึ่งเราสามารถเลือกที่จะ"ไม่สนใจ"หรือ"สนใจ"ค่า exit status ของ thread ได้ดังในตัวอย่างช่วงที่ 1 และ 2 ตามลำดับ

```
$ make
$ cd output 
$ ./pthread_basic
[---01-------------------------]
main(30)
printer1: 0
printer1: 1
printer1: 2
printer1: 3
printer1: 4
printer1: 5
printer1: 6
printer1: 7
printer1: 8
printer1: 9
main(33)
[---02-------------------------]
main(45)
printer2: 0
printer2: 1
printer2: 2
printer2: 3
printer2: 4
printer2: 5
printer2: 6
printer2: 7
printer2: 8
printer2: 9
main(48) return value of thread is -1
----------------------------

```


