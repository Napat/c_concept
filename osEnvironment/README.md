

To get more information about `environ` variable
```
man environ
```


Note: DO NOT modify `environ` variable by yourself; 
use the `setenv` and `unsetenv` function instead.

```
$ env
SHELL=/bin/bash
TERM=xterm
DOCKER_HOST=tcp://0.0.0.0:2375
USER=napat
...

$
$ ./output/env

---Part 1---------------------
SHELL=/bin/bash
TERM=xterm
DOCKER_HOST=tcp://0.0.0.0:2375
USER=napat
...

++++
MYPROGRAM_TCPPORT=4321

---Part 2---------------------
Now using tcp port: 4321

---Part 3---------------------
Not found environment variable: MYPROGRAM_TCPPORT
Now using tcp port: 4444

```



