.POSIX:

PROJECTDIR = ../..
include $(PROJECTDIR)/scripts/rules.mk

OBJS =\
	fromepoch.o\
	totime.o\
	canonical.o\
	getstat.o\
	setstat.o\

TARGET = libscc-posix.a

all: $(TARGET)

$(TARGET): $(OBJS)
	$(AR) $(PROJ_ARFLAGS) $@ $?
	$(RL) $(PROJ_RLFLAGS) $@
	cp $@ $(LIBDIR)/scc
