## Class in lowercase EX: cst240
CLASS = cst240
## Class section number EX: section1
SECTION = section1
## Assignment lab number EX: lab05 
LAB = lab01

############# DO NOT EDIT BELOW THIS LINE ################
USER := ${LOGNAME}
SUB_TAR_FILE := $(CLASS)+$(SECTION)+$(LAB)+$(USER).tar
SUB_PROG = /home/grader_dev/src/cp_files

TAR_CREATE:
	@-rm -f *.o
	@-tar -cf $(SUB_TAR_FILE) *.[ch] [Mm]akefile ||:

sub: TAR_CREATE
	@-$(SUB_PROG) $(SUB_TAR_FILE) ||:
	@-rm -f $(SUB_TAR_FILE) ||:
