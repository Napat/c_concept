# SFTP

โปรโตคอล FTP เป็นโปรโตคอลที่ได้รับความนิยมอย่างมากในการรับส่งไฟล์ระหว่างเครื่อง
แต่ในการใช้งานจริงความปลอดภัยของโปรโตคอลการสื่อสารเป็นเรื่องที่เราต้องให้ความสำคัญ
ดังนั้นในโปรแกรมนี้จะเป็นตัวอย่างการใช้งานโปรโตคอล sftp ด้วย libcurl
ทั้งนี้หากติดตั้ง libcurl โดย default แล้วมักจะไม่ support sftp จำเป็นจะต้องมี libssh2
และในการ compile libcurl ต้องใส่ ./configure --with-libssh2 เอาไว้ด้วย
สามารถตรวจสอบโปรโตคอลที่รองรับได้ด้วยคำสั่ง

## Install LIBCURL with SFTP

- Installation Link: http://andrewberls.com/blog/post/adding-sftp-support-to-curl
- https://github.com/curl/curl/blob/master/docs/INSTALL.md
- https://www.libssh2.org/download/libssh2-1.9.0.tar.gz

Install LIBSSH2

``` bash
wget --no-check-certificate https://www.libssh2.org/download/libssh2-1.9.0.tar.gz
tar -xvzf libssh2-1.9.0.tar.gz
cd libssh2-1.9.0/
./configure
make
sudo make install
```

Now, install CURL with SFTP

``` bash
sudo apt-get install build-essential
wget --no-check-certificate http://curl.haxx.se/download/curl-7.68.0.tar.gz
tar -xvzf curl-7.68.0.tar.gz
cd curl-7.68.0
./configure --with-libssh2=/usr/local
make
sudo make install
sudo ldconfig               # https://github.com/curl/curl/issues/4448
curl -V | grep sftp
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
12345678901234567890
$
$ ./sftpclient
12345678901234567
$
$ ls gettofile.*
gettofile.bin  gettofile.bin_2
$ cat gettofile.bin
12345678901234567890
$
$ cat gettofile.bin_2
12345678901234567890
$
$ ls ../simulate_sftpserver/share/
putfile  testfile
$
$ cat ../simulate_sftpserver/share/putfile
1234567890as34567890
```

## tools

- [sftp server using docker](https://github.com/fixate/docker-sftp)

## Other Resource

- https://curl.haxx.se/libcurl/c/sftpget.html
- https://curl.haxx.se/libcurl/c/sftpuploadresume.html
- https://curl.haxx.se/libcurl/c/CURLOPT_RESUME_FROM.html
- https://curl.haxx.se/libcurl/c/CURLOPT_RESUME_FROM_LARGE.html
