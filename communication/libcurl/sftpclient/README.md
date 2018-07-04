# SFTP

โปรโตคอล FTP เป็นโปรโตคอลที่ได้รับความนิยมอย่างมากในการรับส่งไฟล์ระหว่างเครื่อง
แต่ในการใช้งานจริงความปลอดภัยของโปรโตคอลการสื่อสารเป็นเรื่องที่เราต้องให้ความสำคัญ
ดังนั้นในโปรแกรมนี้จะเป็นตัวอย่างการใช้งานโปรโตคอล sftp ด้วย libcurl
ทั้งนี้หากติดตั้ง libcurl โดย default แล้วมักจะไม่ support sftp จำเป็นจะต้องมี libssh2
และในการ compile libcurl ต้องใส่ ./configure --with-libssh2 เอาไว้ด้วย
สามารถตรวจสอบโปรโตคอลที่รองรับได้ด้วยคำสั่ง

``` bash
$ /usr/local/bin/curl -V
curl 7.61.0-DEV (x86_64-pc-linux-gnu) libcurl/7.61.0-DEV OpenSSL/1.0.2g zlib/1.2.8 libssh2/1.8.1_DEV
Release-Date: [unreleased]
Protocols: dict file ftp ftps gopher http https imap imaps pop3 pop3s rtsp scp sftp smb smbs smtp smtps telnet tftp
Features: AsynchDNS IPv6 Largefile NTLM NTLM_WB SSL libz TLS-SRP UnixSockets HTTPS-proxy
```

## Start sftp server

หากใครยังไม่มี sftp server สามารถใช้ docker-compose เพื่อจำลองการทำงานของ sftp สำหรับทดสอบโปรแกรมได้ดังนี้

``` bash
$ cd simulate_sftpserver
$ docker-compose up
Starting simulate_sftpserver_sftp_1 ... done
Attaching to simulate_sftpserver_sftp_1
sftp_1  | [entrypoint] Parsing...
...
+----[SHA256]-----+
sftp_1  | [entrypoint] Executing sshd
sftp_1  | Server listening on 0.0.0.0 port 22.
sftp_1  | Server listening on :: port 22.
```

โดยในที่นี้จะ map port ไว้ที่ port 2222 นะครับ สามารถอ่านรายละเอียดได้จาก docker-compose.yaml เลย

## ทดสอบโปรแกรม


``` bash
# Open new terminal
$ make
$ cd output
$ ls gettofile.bin
ls: cannot access 'gettofile.bin': No such file or directory
$ ls ../simulate_sftpserver/share/
testfile
$ cat ../simulate_sftpserver/share/testfile
1234567890
$
$ ./sftpclient
$ ls gettofile.bin
gettofile.bin
$ cat gettofile.bin
1234567890
$
$ ls ../simulate_sftpserver/share/
putfile  testfile
$ cat ../simulate_sftpserver/share/putfile
1234567890
$ 
```

## tools 

- [sftp server using docker](https://github.com/fixate/docker-sftp)
