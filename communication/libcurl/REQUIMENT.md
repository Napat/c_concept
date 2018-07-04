# Install libcurl to system

## Debian

``` bash
sudo apt-get install libcurl4-openssl-dev
```

## Building from git

``` bash
# First, remove default curl
sudo apt-get remove curl

# clone curl source
git clone https://github.com/curl/curl.git
cd curl
cat GIT-INFO
cat docs/INSTALL.md
```

ในขั้นนี้อาจจะต้องติดตั้งโปรแกรมเพิ่มเติมประมาณนี้
- autoconf version 2.57 or newer `sudo apt install autoconf`
- libtoolize 1.4.2 or newer `sudo apt install libtool`

``` bash
cd <curl source>
./buildconf     # require autoconf version 2.57 or newer

# Method1: Basic config libcurl but not support sftp
# ./configure --prefix=$HOME
#
# Method2: To enable support sftp we need somthing like 
## Install libssh2
# git clone https://github.com/libssh2/libssh2.git
# cd libssh2
# ./buildconf
# ./configure --prefix=/usr   # or ./configure --prefix=/usr/local
# make
# sudo make install
#
# cd <curl source>
# ./configure --with-libssh2=/usr --prefix=/usr     # or ./configure --with-libssh2=/usr/local --prefix=/usr/local # or add --disable-shared for not shared lib .so
#
# Or maybe follow the instruction in: http://andrewberls.com/blog/post/adding-sftp-support-to-curl


make
make test # (optional)
make install

```

``` bash
# Get support features case: Basic config but no sftp
$ curl -V
curl 7.47.0 (x86_64-pc-linux-gnu) libcurl/7.47.0 GnuTLS/3.4.10 zlib/1.2.8 libidn/1.32 librtmp/2.3
Protocols: dict file ftp ftps gopher http https imap imaps ldap ldaps pop3 pop3s rtmp rtsp smb smbs smtp smtps telnet tftp
Features: AsynchDNS IDN IPv6 Largefile GSS-API Kerberos SPNEGO NTLM NTLM_WB SSL libz TLS-SRP UnixSockets

# Get support features case: curl with sftp
$ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib/
$ echo $LD_LIBRARY_PATH
/usr/local/lib/
$ /usr/local/bin/curl -V
curl 7.61.0-DEV (x86_64-pc-linux-gnu) libcurl/7.61.0-DEV OpenSSL/1.0.2g zlib/1.2.8 libssh2/1.8.1_DEV
Release-Date: [unreleased]
Protocols: dict file ftp ftps gopher http https imap imaps pop3 pop3s rtsp scp sftp smb smbs smtp smtps telnet tftp
Features: AsynchDNS IPv6 Largefile NTLM NTLM_WB SSL libz TLS-SRP UnixSockets HTTPS-proxy

```

