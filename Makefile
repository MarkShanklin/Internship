############################################################
# File Name     : Makefile
# Purpose       : Compiles the code using gcc.
# Creation Date : 06-27-2016
# Last Modified : Mon 27 Jun 2016 02:34:56 PM PDT
# Created By    : Mark Shanklin 
###########################################################

C = gcc -g
CFLAGS = -Wall 
PROG = Internship
SOURCES := $(shell echo *.c)
DEPS := $(shell echo *.h)
OBJECTS = $(SOURCES:.c=.o)
DEPENDS = depends.mk
$(shell touch ${DEPENDS})

all: depends $(PROG)

$(PROG): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -f $(PROG) *.o $(DEPENDS)

include $(DEPENDS)

depends:
	gcc -MM $(SOURCES) > $(DEPENDS)
