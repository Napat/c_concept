# Using libcurl to make restapi client

## Install libcurl to system

See [REQUIMENT.md](REQUIMENT.md)

## Let's begin

แม้การเขียนโปรแกรมในช่วงเริ่มต้นเพื่อติดต่อกับ rest API ของ http server ด้วยภาษา C ด้วยการเปิด socket จะทำได้ไม่ยากเย็นอะไรนัก  
แต่ในระยะยาวๆเมื่อต้องติดต่อกับโปรโตคอลที่หลากหลายมากขึ้น เช่น https, sftp หรือเมื่อมีความต้องการรองรับ header หลายๆรูปแบบแล้ว  
จะพบว่าเราต้องไปจัดการรายละเอียดอะไรเยอะมากมายเกินกว่าที่เราควรจะต้องไปทำมันเองตัวอย่างเช่น

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



อีกทั้งการที่เราสามารถต่อยอดไปใช้ชุดคำสั่งอื่นๆได้อย่างรวดเร็ว เนื่องจาก library curl ได้เตรียมชุดคำสั่งเยอะแยะมากมายให้เรียกใช้งานได้อย่างง่ายดายกว่าการเขียนเองทั้งหมดอย่างมาก  
ด้วยเหตผลดังกล่าว การใช้ libcurl บนระบบ Unix/Linux จึงได้รับความนิยมอย่างมาก

นอกจากชุดคำสั่งต่างๆแล้ว curl ก็ยังมี tools ที่อำนวยความสะดวกสำหรับการเขียนโปรแกรมให้เราใช้งานเพิ่มเติม ตัวอย่างเช่น

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

### thread safety???

ประเด็นหนึ่งที่ต้องสนใจก็คือเรื่อง thread safety ใครจะใช้ libcurl จำเป็นต้องอ่าน > https://curl.haxx.se/libcurl/c/threadsafe.html
สรุปสั้นๆก็คือ มันมีทั้ง api ที่ thread safety (แต่ก็ยังมีเรื่องที่ว่าต้องสร้าง mutex lock เพิ่มเติมเข้าไป) และแบบไม่ safety (พวก global ทั้งหลาย) ดังนั้นต้อง *เข้าไปอ่านโดยไม่มีข้อแม้*นะครับ

### main.c

``` bash
$ ./output/respapiclient
user_q1 0x603090
user_q2 0x6030b0
user_q3 0x6030d0
user_q3 0x6030f0
curl_get_xN(51) begin----------------------------------------
user pointer: 0x603090
        realsize\size\nmemb 66\1\66
        contents length: 66
        contents: {
 "msg": "Hello World. Today is good day",
 "version": "1.0.0"
}

user pointer: 0x603090
        realsize\size\nmemb 66\1\66
        contents length: 66
        contents: {
 "msg": "Hello World. Today is good day",
 "version": "1.0.0"
}

user pointer: 0x603090
        realsize\size\nmemb 66\1\66
        contents length: 66
        contents: {
 "msg": "Hello World. Today is good day",
 "version": "1.0.0"
}

curl_get_xN(56) end----------------------------------------
curl_post_json_xN(87) begin----------------------------------------
user pointer: 0x6030b0
        realsize\size\nmemb 46\1\46
        contents length: 46
        contents: {
 "msg": "Hello POST.",
 "version": "1.0.1"
}
user pointer: 0x6030b0
        realsize\size\nmemb 46\1\46
        contents length: 46
        contents: {
 "msg": "Hello POST.",
 "version": "1.0.1"
}
user pointer: 0x6030b0
        realsize\size\nmemb 46\1\46
        contents length: 46
        contents: {
 "msg": "Hello POST.",
 "version": "1.0.1"
}
curl_post_json_xN(92) end----------------------------------------
curl_post_xml_xN(128) begin----------------------------------------
user pointer: 0x6030d0
        realsize\size\nmemb 53\1\53
        contents length: 53
        contents: {
 "msg": "Hello POST xml.",
 "version": "1.0.2"
}
user pointer: 0x6030d0
        realsize\size\nmemb 53\1\53
        contents length: 53
        contents: {
 "msg": "Hello POST xml.",
 "version": "1.0.2"
}
user pointer: 0x6030d0
        realsize\size\nmemb 53\1\53
        contents length: 53
        contents: {
 "msg": "Hello POST xml.",
 "version": "1.0.2"
}
curl_post_xml_xN(133) end----------------------------------------
curl_post_appxwwwformurlencoded_xN(172) begin----------------------------------------
user pointer: 0x6030f0
        realsize\size\nmemb 82\1\82
        contents length: 82
        contents: {
 "msg": "tasks_post-x-www-form-urlencoded/v1/compareface",
 "version": "1.0.3"
}
user pointer: 0x6030f0
        realsize\size\nmemb 82\1\82
        contents length: 82
        contents: {
 "msg": "tasks_post-x-www-form-urlencoded/v1/compareface",
 "version": "1.0.3"
}
user pointer: 0x6030f0
        realsize\size\nmemb 82\1\82
        contents length: 82
        contents: {
 "msg": "tasks_post-x-www-form-urlencoded/v1/compareface",
 "version": "1.0.3"
}
curl_post_appxwwwformurlencoded_xN(177) end----------------------------------------
$
```


## References

- [libcurl c api document](https://curl.haxx.se/libcurl/c/)
- [libcurl github](https://github.com/curl/curl/blob/master/docs/INSTALL.md)
- [libcurl example: getinmemory](https://curl.haxx.se/libcurl/c/getinmemory.html)
- [libcurl tutorial](https://curl.haxx.se/libcurl/c/libcurl-tutorial.html)
- [restful tutorial](http://www.drdobbs.com/web-development/restful-web-services-a-tutorial/240169069)

## Userful
- [mocky rest api server support both http/https](https://www.mocky.io/)
- [mockable rest api](https://www.mockable.io/)



