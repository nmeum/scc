.POSIX:

LIBS  =\
	libcrt\
	libscc\
	libscc-$(DRIVER)\
	libmach\

DIRS  =\
	cmd\
	$(LIBS)\

PROJECTDIR = ..
include $(PROJECTDIR)/scripts/rules.mk

NODEP = 1

all: cmd

cmd: $(LIBS)
