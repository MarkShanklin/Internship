############################################################
# File Name     : Makefile
# Purpose       : Compiles the code using gcc.
# Creation Date : 06-27-2016
# Last Modified : Tue 05 Jul 2016 12:34:42 PM PDT
# Created By    : Mark Shanklin 
###########################################################

C = gcc —std=‘c1x’ g
CFLAGS = -Wall 
PROG1 = FileObserver.prog
PROG2 = Submission.prog
#PROG3 = Listener.prog

SOURCES1 = fileObs.c
SOURCES2 = Submission.c
#SOURCES3 = Listener.c

DEPS := $(shell echo *.h)
	
OBJECTS1 = $(SOURCES1:.c=.o)
OBJECTS2 = $(SOURCES2:.c=.o)
#OBJECTS3 = $(SOURCES3:.c=.o)

DEPENDS = depends.mk
$(shell touch ${DEPENDS})

all: depends $(PROG1) $(PROG2) $(PROG3)

$(PROG1): $(OBJECTS1)
	$(CC) $(CFLAGS) -o $@ $^

$(PROG2): $(OBJECTS2)
	$(CC) $(CFLAGS) -o $@ $^

#$(PROG3): $(OBJECTS3)
#	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -f $(PROG1) $(PROG2) *.o $(DEPENDS)

include $(DEPENDS)

depends:
	gcc -MM $(SOURCES1) > $(DEPENDS)
	gcc -MM $(SOURCES2) > $(DEPENDS)
#	gcc -MM $(SOURCES3) > $(DEPENDS)
