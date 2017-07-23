
# Ubuntu workaround when error no lib/header
```
fatal error: gdbm.h: No such file or directory
#include <gdbm.h>
```

## Sol1:  
Search for `gdmb.h` in `https://packages.ubuntu.com/`
You will found that `libgdbm-dev` contains `gdmb`.
`sudo apt-get install libgdbm-dev`


## Sol2:  
In ubuntu there is `apt-file` package that allows you to find package which contains specified file. 
```
sudo apt-get install apt-file
# update the cache with
apt-file update
# to search the package you need with
apt-file search gdbm.h

<output>
courier-doc: /usr/share/doc/courier-doc/htmldoc/maildropgdbm.html
libgdbm-dev: /usr/include/gdbm.h
maildrop: /usr/share/doc/maildrop/html/maildropgdbm.html
pike7.8-reference: /usr/share/doc/pike7.8-doc/html/reference/ex/predef_3A_3A/Gdbm/gdbm.html
python2.7-doc: /usr/share/doc/python2.7/html/library/gdbm.html
slang-gdbm: /usr/share/slsh/local-packages/help/gdbm.hlp
<output end>

sudo apt-get install libgdbm-dev
```

