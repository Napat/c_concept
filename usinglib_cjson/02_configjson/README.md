More: https://github.com/DaveGamble/cJSON  

```
$ make
$ cd output
$ ./jsonconfig

main(408) ---STEP 1---

main(412) ---STEP 2---

{
        "name": "easyswitch",
        "snmp_enable":  false,
        "telnet_enable":        {
                "1":    true,
                "2":    true,
                "3":    true,
                "4":    true
        },
        "ports":        [{
                        "port_name":    "port01",
                        "port_enable":  false,
                        "port_type":    0
                }, {
                        "port_name":    "port02",
                        "port_enable":  false,
                        "port_type":    0
                }, {
                        "port_name":    "port03",
                        "port_enable":  false,
                        "port_type":    0
                }, {
                        "port_name":    "port04",
                        "port_enable":  false,
                        "port_type":    0
                }]
}

main(416) ---STEP 3---
print_runinfo(386) switch info
         name: bangkok01
         snmp_enable: 1
         telnet_enable: 1/1/0/0
         port[0]: name:p1 status:1 type:1
         port[1]: name:p2 status:0 type:1
         port[2]: name:p3 status:0 type:2
         port[3]: name:p4 status:1 type:2


main(438) ---STEP 4---
print_runinfo(386) switch info
         name: easyswitch
         snmp_enable: 0
         telnet_enable: 1/1/1/1
         port[0]: name:port01 status:0 type:0
         port[1]: name:port02 status:0 type:0
         port[2]: name:port03 status:0 type:0
         port[3]: name:port04 status:0 type:0

$
$ cat cfgstart.json
{
        "name": "easyswitch",
        "snmp_enable":  false,
        "telnet_enable":        {
                "1":    true,
                "2":    true,
                "3":    true,
                "4":    true
        },
        "ports":        [{
                        "port_name":    "port01",
                        "port_enable":  false,
                        "port_type":    0
                }, {
                        "port_name":    "port02",
                        "port_enable":  false,
                        "port_type":    0
                }, {
                        "port_name":    "port03",
                        "port_enable":  false,
                        "port_type":    0
                }, {
                        "port_name":    "port04",
                        "port_enable":  false,
                        "port_type":    0
                }]
}
$
```

