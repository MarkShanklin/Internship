# R Jesse Chaney
# 

CC = gcc
DEBUG = -g
DEFINES = -DDEBUG

CFLAGS = $(DEBUG) -Wall -Wshadow -Wunreachable-code -Wredundant-decls \
        -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes \
        -Wdeclaration-after-statement $(DEFINES)
PROGS = getpwent

all: $(PROGS)

getpwent: getpwent.o
	$(CC) $(CFLAGS) -o $@ $^

getpwent.o: getpwent.c
	$(CC) $(CFLAGS) -c $<

# clean up the compiled files and editor chaff
clean:
	rm -f $(PROGS) *.o *~ \#* rev_numbers.txt
