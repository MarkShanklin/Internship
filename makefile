#$(shell touch depends.mk)
#include depends.mk
PROG = fileobs
TAR_FILE = $(PROG)_${LOGNAME}.tar.gz
GC = bash -i -c gitCom#${LAB}
CC = gcc -g -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement



all: $(PROG)

$(PROG): $(PROG).o 
	$(CC) -o $@ $^

$(PROG).o: $(PROG).c $(PROG).h
	$(CC) -c $<

#main.o: main.c $(PROG).h
#	$(CC) -c $<

clean:
	rm -f *.o *.mk $(PROG) *~ \#* 


tar: clean
	rm -f $(TAR_FILE)
	$(GC) $(PROG) All
	tar cvfz $(TAR_FILE) *.[ch] ?akefile *.bash
		#create verbose outfile file name and gzip the result

git: clean
	$(GC) ${LAB}

test1:

depend:
	gcc -MM *.c > depends.mk

