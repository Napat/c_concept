๋
About JSON
-----
JSON (JavaScript Object Notation) คือ รูปแบบของข้อมูลแบบหนึ่งมีลักษณะการเก็บข้อมูลคล้ายกับไฟล์แบบ XML  
แต่กำลังได้รับความนิยมมากกว่าเนื่องจากข้อมูลที่มีขนาดเล็กกว่า สามารถทำความเข้าใจได้ง่าย และสามารถถูกสร้างและอ่านโดยเครื่องได้ง่าย  

ในปัจจุบันได้มีการนำ JSON ไปประยุกต์ใช้อย่างแพร่หลาย ตัวอย่างเช่น ใช้แลกเปลี่ยนข้อมูลระหว่างกัน ใช้สร้างไฟล์ config  
หรือแม้กระทั่งนำไปใช้ออกแบบฐานข้อมูล(database) แบบ nosql ในหลายๆเจ้าเช่น firebase เป็นต้น  

[cJason](https://github.com/DaveGamble/cJSON)
-----
ในหลายๆภาษารองรับการทำงานร่วมกับข้อมูล JSON โดยตัวภาษาเลย แต่ในภาษา C ไม่มีความสามารถดังกล่าว  
แต่ทั้งนี้ทั้งนั้นก็มีผู้พัฒนา library สำหรับทำงานร่วมกับไฟล์ JSON ขึ้นมาอยู่หลากหลายเจ้า  
เจ้าหนึ่งที่ถูกเลือกนำมาใช้ในที่นี้ก็คือ [cJason](https://github.com/DaveGamble/cJSON) เนื่องจากมีการพัฒนาที่ต่อเนื่องและยัง active อยู่ 
สามารถใช้งานได้อย่างง่ายดายเพียงแค่นำไฟล์ cJASON.c/.h เข้ามาในโปรเจค  
รวมถึงเป็น License แบบ MIT ที่มีลักษณะเป็นสัญญาอนุญาตซอฟต์แวร์เสรีที่มีข้อจำกัดน้อย (Permissive License) อีกด้วย  


