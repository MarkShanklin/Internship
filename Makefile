############################################################
# File Name     : Makefile
# Purpose       : Compiles the code using gcc.
# Creation Date : 06-27-2016
# Last Modified : Wed 06 Jul 2016 10:16:32 AM PDT
# Created By    : Mark Shanklin 
###########################################################

CC = gcc
CFLAGS = -g -Wall -std='gnu11' 
PROG = Sub.prog
SOURCES = $(shell echo *.h)
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
	$(CC) -MM $(SOURCES) > $(DEPENDS)
