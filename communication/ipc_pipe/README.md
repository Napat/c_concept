
pipe: The unidirectional data channel for interprocess communication(IPC).  
ใช้สำหรับสื่อสารกันแบบทางเดียวระหว่าง processes ตัวอย่างการใช้งานเช่น  
threadA ต้องการส่งข้อมูลไปยัง threadB อยู่เสมอๆ เป็นต้น    
  
```
$ make
$ ./output/pipe_example
Parent process
Child process
End, pid=0
Rx data: Hello world!
End, pid=303
```
