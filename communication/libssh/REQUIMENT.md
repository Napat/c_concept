# Libssl development

## Requirements

- [cmake](https://api.libssh.org/stable/index.html)
- [openssl](http://www.openssl.org)
- [libssl](https://www.libssh.org/)

## install cmake & fix issues

``` bash
$ sudo apt install cmake

# but some thing wrong: https://stackoverflow.com/a/38896967/3616311
$ cmake -version
cmake: /usr/local/lib/libcurl.so.4: no version information available (required by cmake)

$ locate libcurl.so.4
/usr/lib/x86_64-linux-gnu/libcurl.so.4
/usr/lib/x86_64-linux-gnu/libcurl.so.4.5.0
$ ls -l /usr/local/lib/libcurl.so.4
lrwxrwxrwx 1 root root 16 Jan 24  2020 /usr/local/lib/libcurl.so.4 -> libcurl.so.4.6.0
$ sudo rm /usr/local/lib/libcurl.so.4
$ sudo ln -s /usr/lib/x86_64-linux-gnu/libcurl.so.4.5.0 /usr/local/lib/libcurl.so.4
$ ls -l /usr/local/lib/libcurl.so.4
lrwxrwxrwx 1 root root 42 Feb  1 15:20 /usr/local/lib/libcurl.so.4 -> /usr/lib/x86_64-linux-gnu/libcurl.so.4.5.0

# retest cmake
$ cmake -version
cmake version 3.10.2
CMake suite maintained and supported by Kitware (kitware.com/cmake).
```

## libssh-dev compilation from source file

install to path: `/mnt/d/workdir/c_concept/communication/libssh/tmp/usr`

``` bash
$ mkdir tmp && cd tmp
$ wget --no-check-certificate https://www.libssh.org/files/0.9/libssh-0.9.0.tar.xz
$ tar xvf libssh-0.9.0.tar.xz
$ cd libssh-0.9.0/doc
$ cat INSTALL
$ cmake -DUNIT_TESTING=OFF -DCMAKE_INSTALL_PREFIX=/mnt/d/workdir/c_concept/communication/libssh/tmp/usr -DCMAKE_BUILD_TYPE=Debug ..
### or for release with min size: 
### cmake -DUNIT_TESTING=OFF -DCMAKE_INSTALL_PREFIX=/mnt/d/workdir/c_concept/communication/libssh/tmp/usr -DCMAKE_BUILD_TYPE=MinSizeRel ..
$ make
$ make install
$ tree /mnt/d/workdir/c_concept/communication/libssh/tmp/usr
/mnt/d/workdir/c_concept/communication/libssh/tmp/usr
├── include
│   └── libssh
│       ├── callbacks.h
│       ├── legacy.h
│       ├── libssh.h
│       ├── libsshpp.hpp
│       ├── server.h
│       ├── sftp.h
│       └── ssh2.h
└── lib
    ├── cmake
    │   └── libssh
    │       ├── libssh-config-version.cmake
    │       └── libssh-config.cmake
    ├── libssh.so -> libssh.so.4
    ├── libssh.so.4 -> libssh.so.4.8.1
    ├── libssh.so.4.8.1
    └── pkgconfig
        └── libssh.pc
```

## Howto using libssh

Compile application

``` bash
gcc main.c -L/mnt/d/workdir/c_concept/communication/libssh/tmp/usr/lib -lssh -I/mnt/d/workdir/c_concept/communication/libssh/tmp/usr/include -o myapp.out
```

Execute application

``` shell
#!/bin/sh
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/mnt/d/workdir/c_concept/communication/libssh/tmp/usr/lib
./myapp.out
```

## references

- [libssl](https://www.libssh.org/)
- [libssl is the portion of OpenSSL which supports TLS](https://wiki.openssl.org/index.php/Libssl_API)
- [tutorial](https://api.libssh.org/stable/)
