

all: testapp

testapp: indentcode checkdiff
	gcc test_ready.c -o $@ 

indentcode: FORCE
	./Lindent test.c -o test_ready.c

# Note, diff return: 0 means no differences found, 1 means differences found, grather or equal 2 means error
checkdiff: FORCE
	diff -u test.c test_ready.c; [ $$? -lt 2 ]

clean: FORCE
	rm -rf testapp *.o test_ready.c

FORCE:

