# About Endianess
เป็นเรื่องของการเรียงลำดับความสำคัญของไบท์ข้อมูล (byte order) ว่า address ที่มีความสำคัญสูงจะถูกเห็บก่อนหรือเก็บทีหลัง การเรียงลำดับนี้จะถูกกำหนดมาตั้งแต่ขั้นตอนการเลือกใช้งาน cpu แล้วว่าเครื่อง ( machine) ที่ใช้งานจะเป็นประเภท Big หรือ Little endian  
ฺ
### Big endian   
ไบท์ของข้อมูลที่มีความสำคัญสูงกว่าจะถูกเก็บก่อน ตัวอย่างเช่น 
การเก็บตัวเลขค่า 305,419,896 = 0x12345678 แบบ Big endian จะถูกเก็บค่าดังนี้  
  
| Address | Value |
|---|---|
| Base Addr + 0 | 0x12 |
| Base Addr + 1 | 0x34 |
| Base Addr + 2 | 0x56 |
| Base Addr + 3 | 0x78 |

### Little endian   
ไบท์ของข้อมูลที่มีความสำคัญสูงกว่าจะถูกเก็บก่อน ตัวอย่างเช่น 
การเก็บตัวเลขค่า 305,419,896 = 0x12345678 แบบ Little endian จะถูกเก็บค่าดังนี้  
  
| Address(byte) | Value |
|---|---|
| Base Addr + 0 | 0x78 |
| Base Addr + 1 | 0x56 |
| Base Addr + 2 | 0x34 |
| Base Addr + 3 | 0x12 |

### Network byte order 
การส่งข้อมูลข้าม network เช่น Internet protocol นั้นมีแบบแผน (conventional) หนึ่งที่ตกลงกันไว้ว่าจะใช้ **Big-endian** ในการส่งข้อมูลสื่อสารระหว่างกัน   
  
# Using endiancheker API  
ทดสอบเรียก API เพื่อตรวจสอบด้วยเครื่องที่เป็น little endian (cpu: Intel i386/x64) จะได้ผลลัพธ์ดังนี้  
```
$ make clean & make
$ ./output/endianess_checker
This machine is LITTLE endian
``` 

หากเรียก API เพื่อตรวจสอบด้วยเครื่องที่เป็น big endian เช่น cpu ของ Motolor จะได้ผลลัพธ์ดังนี้  
```
$ make clean & make
$ ./output/endianess_checker
This machine is BIG endian
``` 

