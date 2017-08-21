  
Note: See `ubuntu_workaround.md` for requirements package.


```
$ make
$ ./a.out
Example
./binary insert 1 Myfirstname Mylastname Newyork 1986
./binary delete 1
./binary show 1
./binary showall
$
$ ./a.out insert 1 Napat Rc Bangkok 1986
$ ./a.out insert 2 Elon Musk California 1971
$ ./a.out insert 3 Steve Jobs California 1955
$ ./a.out insert 4 Bill Gates Washington 1955
$
$  ./a.out show 2
key id: 2
firstname: Elon
lastname: Musk
city: California
yearofbirth: 1971
$
$
$ ./a.out showall
key id: 1
firstname: Napat
lastname: Rc
city: Bangkok
yearofbirth: 1986

key id: 2
firstname: Elon
lastname: Musk
city: California
yearofbirth: 1971

key id: 3
firstname: Steve
lastname: Jobs
city: California
yearofbirth: 1955

key id: 4
firstname: Bill
lastname: Gates
city: Washington
yearofbirth: 1955

$ ls *.sdb
customers.sdb
$ 
$ ./a.out delete 3
$ ./a.out showall
key id: 1
firstname: Napat
lastname: Rc
city: Bangkok
yearofbirth: 1986

key id: 2
firstname: Elon
lastname: Musk
city: California
yearofbirth: 1971

key id: 4
firstname: Bill
lastname: Gates
city: Washington
yearofbirth: 1955

$
$
```

