#Created By: Mark Shanklin
#My Makefile

CC = gcc -g
CFLAGS=-Wall -std='gnu11' -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement 
SOURCES = $(shell echo *.c) $(shell echo ../TLPI/*.c)
DEPS := $(shell echo *.h) $(shell echo ../TLPI/*.h)
OBJECTS = $(SOURCES:.c=.o)
DEPENDS = depends.mk
$(shell touch ${DEPENDS})

PROG= test.prog

all: depends $(PROG)

clean:
	rm -f $(OBJECTS)
	rm -f $(PROG)

$(PROG): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

include $(DEPENDS)

depends:
	$(CC) -MM $(SOURCES) > $(DEPENDS)
