  
Note: See `ubuntu_workaround.md` for gdbm requirements package.


```
$ make
$ cd output 
$ ./sgdbm
Example
 ./binary insert hashkey1 1 firstname lastname city 1986
 ./binary update key1 2 fname lname city 1987
 ./binary delete key1
 ./binary show key1
$
$ ./sgdbm insert key1 1 f1 l1 bbk 1986
Insert key key1 complete!!
$
$ ./sgdbm show key1
KEY: key1
         id: 1
         firstname: f1
         lastname: l1
         city: bbk
         yearofbirth: 1986

$ ./sgdbm update key1 1 f01 l01 bbk 1987
Update key key1 complete!!
$ 
$  ./sgdbm show key1
KEY: key1
         id: 1
         firstname: f01
         lastname: l01
         city: bbk
         yearofbirth: 1987

$ 
$  ./sgdbm update key2 2 f02 l02 bbk 1988
Update key key2 complete!!
$ ./sgdbm update key3 3 f03 l03 au 1989
Update key key3 complete!!
$  ./sgdbm insert key3 3 f03 l03 au 1989
sgdbm_insert(53) insert error, expect key 'key3' is already in database
$  ./sgdbm delete key3
$  ./sgdbm insert key3 3 f03 l03 au 1989
Insert key key3 complete!!
$ ./sgdbm showall
KEY: key3
         id: 3
         firstname: f03
         lastname: l03
         city: au
         yearofbirth: 1989

KEY: key1
         id: 1
         firstname: f01
         lastname: l01
         city: bbk
         yearofbirth: 1987

KEY: key2
         id: 2
         firstname: f02
         lastname: l02
         city: bbk
         yearofbirth: 1988

End of database!!

$
$ 
```


--------------------------------------------------------------------
More ref: https://jwhsmith.net/2014/03/lightweight-databases-in-c-gdbm/
```
A simpler implementation

DBM stands for Data Base Management, which is quite self-explanatory : this is a tool used in data management, simple management. Take the basic RDBMS, remove relations, remove table multiplicity, that’s it. DBM allows you to store data in a very simple format : all it does is associating a key to a value for each “row”.

History

Everything started at Bell Labs, with some guy named Ken Thompson (well, this one is pretty famous among UNIX users, actually). He created DBM, which allowed you to :

Create/Initialise a database file.
Close a database (well, one needs to free memory somewhere, right?)
Fetch information using its key.
Storing information (key => value).
Delete an entry using its key.
Getting the first key.
Jumping from one key to the next (lovely queue!).
Now, the big problem with that was : you can’t open more than one database file at the same time, and this can prove itself to be unhandy. For this reason, the University of California created NDBM (New DBM), and guess what : you can open several databases, yay! After this, the Free Software Foundation created GDBM (G for GNU, of course), which brought some additional improvements to the NDBM implementation. In this article, I’ll focus on GDBM directly, as I find it a little bit more convenient to use.

Important notes

GDBM is simple, but there are a few things that come with this lightweight API. I think it is important to know that :

Databases files are locked when opened, a UNIX lock is set. You can disable this mechanism with a flag, but this implies building your own protection mechanism. That’s another GDBM improvement : there was absolutely no protection with NDBM.
Some OSes tend to put some suffixes to the database files when the API creates them. As far as I know, FreeBSD appends .db to the filename. On Debian-based systems, nothing changes. Another interesting fact : if you use NDBM, two files might be created instead of one. Be careful not to mix names up!
A GDBM database is represented by a GDBM_FILE data type. It looks strange at first, but this is a pointer type. GDBM masks our lovely asterisk with a typedef.
Maybe it’s me, but I ran into some data overflow problems when using NDBM : some characters were injected into my DBM entries, no matter how tight my memory management was. If you used a NDBM database without such problems, feel free to contact me.
Anyway, if you develop a simple application, these will probably not become problems.

The API

Prerequisites

You’ll need to include the gdbm.h header file in order to call GDBM routines. You may need to install some packages such as libgdbm-dev or similar (have a look at your distribution-specific documentation).

Routines

Let’s have a look at our routines first :

--------------------------------------------------------------------
GDBM_FILE gdbm_open (const char *name, int block_size, int flags, int mode, void (*fatal_func)(const char *));
void gdbm_close (GDBM_FILE dbf);

typedef struct {
        char *dptr;
        int dsize;
} datum;

int gdbm_store (GDBM_FILE dbf, datum key, datum content, int flag);
datum gdbm_fetch (GDBM_FILE dbf, datum key);
int gdbm_delete (GDBM_FILE dbf, datum key);
datum gdbm_firstkey (GDBM_FILE dbf);
datum datum gdbm_nextkey (GDBM_FILE dbf, datum prev);

const char * gdbm_strerror (gdbm_error errno);
--------------------------------------------------------------------

The first two ones allow you to open and close a database. The datum structure and its 5 routines are meant for data manipulation. The last two ones are here for error handling (they work just like errno routines).

gdbm_open‘s open flags can be set to : GDBM_READER (read-only), GDBM_WRITER (read and write), GDBM_WRCREAT (Read, write, create if necessary), or GDBM_NEWDB (will force database creation no matter what). Some fancy additional flags also exist, such as : GDBM_SYNC (sync on disk after write operations), GDBM_NOLOCK (no locking on the database file) and GDBM_NOMAP (no memory mapping).
The datum structure is a typical dynamically allocated data handler : a pointer to the beginning of the data’s memory area, and its length. Note : datum is used for both the key and the value, meaning you can use anything as a key, as long as it remains unique in your database.
gdbm_store‘s store mode can be either GDBM_INSERT or GDBM_REPLACE. If set to GDBM_INSERT, this parameter will bring the gdbm_store call down if an entry already exists with the given key. Similarly, GDBM_REPLACE will create a new key if it cannot find what it is supposed to replace.
When passing from one key to the next using gdbm_nextkey, you need to specify the previous key in the call (second parameter). I’ll use a loop in the code below, have a look.
Besides those 4 points, everything is quite self-explanatory.
For more information, here’s the magic link : http://www.gnu.org.ua/software/gdbm/manual.html

 Some code

Now, let’s build a simple agenda : a date associated to an event. You can’t have two events at the same time, simple enough ? Let’s do this.

--------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <gdbm.h>

void add_to_agenda(GDBM_FILE db, char* date, char* event){
    datum key, data; // Key and value (date and event).

    key.dptr = date;
    key.dsize = strlen(date);
    data.dptr = event;
    data.dsize = strlen(event);

    // Storing!
    gdbm_store(db, key, data, GDBM_REPLACE);
}

int main(int argc, char** argv)
{
    GDBM_FILE database = gdbm_open("agenda", 512, GDBM_WRCREAT, 0600, NULL);
    if(database == NULL){
        perror("gdbm_open");
        exit(1);
    }

    /*
     * We'll store three events : Christmas Eve, Christmas Day and Boxing Day.
     * I'll just associated the dates to the events using strings.
     */
    add_to_agenda(database, "24/12/2014", "Christmas Eve");
    add_to_agenda(database, "25/12/2014", "Christmas Day");
    add_to_agenda(database, "26/12/2014", "Boxing Day");

    fprintf(stdout, "Now browsing the database...\n");

    datum current_key, current_data;

    /*
     * Basic browsing loop.
     * TIP : the key data pointer is NULL when you reach the end of the queue.
     */
    for(current_key = gdbm_firstkey(database);
        current_key.dptr != NULL;
        current_key = gdbm_nextkey(database, current_key))
    {
        // Fetch the data associated with that key.
        current_data = gdbm_fetch(database, current_key);
        if(current_data.dptr != NULL)
            fprintf(stdout, "\tEvent found : %s on %s.\n", current_data.dptr, current_key.dptr);
    }

    gdbm_close(database);

    return EXIT_SUCCESS;
}
--------------------------------------------------------------------

This sample program produces the following output :

Now browsing the database…
Event found : Christmas Eve on 24/12/2014.
Event found : Christmas Day on 25/12/2014.
Event found : Boxing Day on 26/12/2014.

Now, the system isn’t perfect, but I think that’s a very nice example of easy, simple data storage on UNIX systems. Sometimes, you don’t actually need more, and it is usually a mistake to over-evaluate your needs.

Anyway, that’s it for today. See you next time !
```


