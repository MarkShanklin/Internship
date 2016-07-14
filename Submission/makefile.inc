USER := ${LOGNAME}

SUB_TAR_FILE := $(CLASS)+$(SECTION)+$(LAB)+$(USER).tar

SUB_DIR = /home2/jacob.shanklin/git/Internship/test/

TAR_CREATE:
	tar -cvf $(SUB_TAR_FILE) *.[ch] [Mm]akefile

sub: TAR_CREATE
	mv $(SUB_TAR_FILE) $(SUB_DIR)
