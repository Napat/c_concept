# Using libcurl to make restapi client

## Install libcurl to system

See [REQUIMENT.md](../REQUIMENT.md)

## Let's begin

แม้การเขียนโปรแกรมเพื่อติดต่อกับ rest API ของ http server ด้วยภาษา C ด้วยการเปิด socket ด้วยรูปแบบมาตรฐานจะทำได้ไม่ยากเย็นอะไรนัก

``` http port 80 http://www.mocky.io/v2/5185415ba171ea3a00704eed
$ telnet www.mocky.io 80
GET /v2/5185415ba171ea3a00704eed HTTP/1.1
Host: www.mocky.io
```

``` https port 443 https://stackoverflow.com/questions
$ openssl s_client -connect stackoverflow.com:443
GET /questions HTTP/1.1
Host: stackoverflow.com
```

แต่เมื่อมีความต้องติดต่อกับ header หลายๆรูปแบบหรือเมื่อมี requirements ว่าอยากติดต่อกับโปรโตคอลที่หลากหลายมากขึ้น เช่น https, sftp แล้ว  
จะพบว่าเราต้องไปจัดการรายละเอียดอะไรเยอะมากมายและเสียเวลาในการพัฒนามากเกินไป
เพื่อแก้ปัญหานี้การใช้งาน library ที่ชื่อว่า curl จึงก้าวเข้า

การใช้งาน curl เราสามารถต่อยอดไปใช้ชุดคำสั่งอื่นๆได้อย่างรวดเร็ว 
เพราะมีชุดคำสั่งเยอะแยะมากมายให้เรียกใช้งานได้อย่างง่ายดายกว่าการเขียนเองทั้งหมดอย่างมาก  
ด้วยเหตผลดังกล่าว การใช้ libcurl บนระบบ Unix/Linux จึงได้รับความนิยมอย่างมาก

นอกจากชุดคำสั่งต่างๆแล้ว curl ก็ยังมี curl-config ซึ่งเป็น tools ที่อำนวยความสะดวกสำหรับการเขียนโปรแกรมให้เราใช้งานเพิ่มเติม ตัวอย่างเช่น

`curl-config --cflags`: ใช้ตรวจสอบข้อมูลเช่น ที่อยู่ของ header, include path ที่จำเป็นต้องใส่ใน cflag โดยทั่วไปแล้วมักจะว่างเปล่าไม่มีค่าอะไรคืนกลับมา

`curl-config --libs`: ใช้หาว่าแฟลกในขั้นตอนการ linking โปรแกรมเข้ากับ libcurl เช่น `-L/usr/lib/x86_64-linux-gnu -lcurl` เป็นต้น

`curl-config --feature`: ใช้ตรวจสอบฟีเจอร์ต่างๆว่า libcurl ที่ติดตั้งสามารถใช้งานฟีเจอร์อะไรได้บ้าง (ฟีเจอร์ต่างๆอาจจะถูกเปิดเพิ่ม/ปิดออกไปในขั้นตอน configure/make library) เช่น หากไม่ได้เปิด SSL ไว้จะสามารถใช้ http, ftp ได้แต่จะไม่สามารถใช้ https, sftp ได้เป็นต้น

``` bash
$ curl-config --feature
SSL
IPv6
UnixSockets
libz
AsynchDNS
IDN
GSS-API
PSL
SPNEGO
Kerberos
NTLM
NTLM_WB
TLS-SRP
HTTP2
HTTPS-proxy
```

`docs/libcurl/libcurl.m4 file`: ในกรณีที่ต้องการสร้าง configure script เพื่อสร้างตัวแปรต่างๆในการเขียนโปรแกรมร่วมกับ libcurl สามารถอ่านวิธีการได้ในไฟล์ดังกล่าว

### thread safety

ประเด็นหนึ่งที่ต้องสนใจก็คือเรื่อง thread safety ใครจะใช้ libcurl จำเป็นต้องอ่าน > https://curl.haxx.se/libcurl/c/threadsafe.html
สรุปสั้นๆก็คือ มันมีทั้ง api ที่ thread safety (แต่ก็ยังมีเรื่องที่ว่าต้องสร้าง mutex lock เพิ่มเติมเข้าไป) และแบบไม่ safety (พวก global ทั้งหลาย) 
ดังนั้นใครที่ใช้งาน libcurl จะต้อง *เข้าไปอ่าน* นะครับ

## References

- [libcurl official example](https://curl.haxx.se/libcurl/c/example.html)
