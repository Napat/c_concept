# Install libcurl to system

## Debian

``` bash
sudo apt-get install libcurl4-openssl-dev
```

## Building from git

``` bash
git clone https://github.com/curl/curl.git
cd curl
cat GIT-INFO
cat docs/INSTALL.md
```

ในขั้นนี้อาจจะต้องติดตั้งโปรแกรมเพิ่มเติมประมาณนี้
- autoconf version 2.57 or newer `sudo apt install autoconf`
- libtoolize 1.4.2 or newer `sudo apt install libtool`

``` bash
./buildconf     # require autoconf version 2.57 or newer
./configure --prefix=$HOME
make
make test (optional)
make install
```

