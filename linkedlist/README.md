
# linked list 
```
// ------------------------------              ------------------------------
// |              |             |            \ |              |             |
// |     DATA     |     NEXT    |--------------|     DATA     |     NEXT    |
// |              |             |            / |              |             |
// ------------------------------              ------------------------------
```


```
$ make
$ cd output 
$ ./linklist_datastructure

-19-llitem_push------------------

cat dolls: 3

-27-llitem_addend------------------

cat dolls: 3
kangaroo dolls: 10

-35-llitem_addend------------------

cat dolls: 3
kangaroo dolls: 10
monkey dolls: 6

-43-llitem_push------------------

bird dolls: 9
cat dolls: 3
kangaroo dolls: 10
monkey dolls: 6

-51-llitem_push------------------

dog dolls: 2
bird dolls: 9
cat dolls: 3
kangaroo dolls: 10
monkey dolls: 6

-59-llitem_addid------------------

bat dolls: 4
dog dolls: 2
bird dolls: 9
cat dolls: 3
rat dolls: 3
kangaroo dolls: 10
monkey dolls: 6
ant dolls: 4

-84-llitem_pop------------------
pop item name: bat dolls, count: 4

dog dolls: 2
bird dolls: 9
cat dolls: 3
rat dolls: 3
kangaroo dolls: 10
monkey dolls: 6
ant dolls: 4

-91-llitem_rmend------------------
dequeue item name: ant dolls, count: 4

dog dolls: 2
bird dolls: 9
cat dolls: 3
rat dolls: 3
kangaroo dolls: 10
monkey dolls: 6

-98-lltime_getitemid------------------
kangaroo dolls is id = 4
cat dolls is id = 2
bird dolls is id = 1
dog dolls is id = 0

-116-lltime_getitemid------------------
stockcount 3 is id = 2
stockcount 5 is id = -1
stockcount 10 is id = 4

-130-lltime_getitemid------------------
kangaroo dolls/10 is id = 4
bird dolls/5 is id = -1
cat dolls/10 is id = -1

-147-lltime_rmbyid------------------

dog dolls: 2
bird dolls: 9
cat dolls: 3
rat dolls: 3
kangaroo dolls: 10
monkey dolls: 6

dog dolls: 2
cat dolls: 3
rat dolls: 3
kangaroo dolls: 10
monkey dolls: 6

-155-lltime_getitem_byid/llitem_setitem_byid------------------

dog dolls: 2
cat dolls: 1
rat dolls: 3
kangaroo dolls: 10
monkey dolls: 6

-165-llitem_setitem_bycmp------------------

dog dolls: 2
cat dolls: 2
rat dolls: 3
kangaroo dolls: 10
monkey dolls: 6

-173-To iterate items------------------
dog dolls
cat dolls
rat dolls
kangaroo dolls
monkey dolls

-183-------------------
$
```


