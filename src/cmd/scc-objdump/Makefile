.POSIX:

PROJECTDIR = ../../..
include $(PROJECTDIR)/scripts/rules.mk

OBJS =\
	main.o\
	coff32.o\
	elf.o\

TARGET = scc-objdump
MORE_LDLIBS = -lmach -lscc -lscc-$(DRIVER)

all: $(TARGET)

scc-objdump: $(OBJS) $(LIBMACH) $(LIBSCC) $(LIBSCC-DRIVER)
	$(CC) $(PROJ_LDFLAGS) $(OBJS) $(PROJ_LDLIBS) -o $@
	cp $@ $(BINDIR)
