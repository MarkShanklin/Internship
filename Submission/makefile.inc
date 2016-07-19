USER := ${LOGNAME}

SUB_TAR_FILE := $(CLASS)+$(SECTION)+$(LAB)+$(USER).tar

SUB_PROG = /home/grader_dev/src/cp_files

TAR_CREATE:
	tar -cvf $(SUB_TAR_FILE) *.[ch] [Mm]akefile

sub: TAR_CREATE
	$(SUB_PROG) $(SUB_TAR_FILE)
	rm -f $(SUB_TAR_FILE)
