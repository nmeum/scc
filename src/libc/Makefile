.POSIX:

PROJECTDIR = ../..
DIRS =\
	assert\
	ctype\
	inttypes\
	locale\
	stdio\
	stdlib\
	string\
	time\
	wchar\
	arch\

include $(PROJECTDIR)/scripts/rules.mk
include rules.mk
include objs/$(ARCH)-$(SYS).mk

NODEP = 1
TARGET = $(LIBC)

all: $(DIRS)
	+@$(MAKE) $(TARGET)

$(LIBC): $(OBJS)
	$(AR) $(ARFLAGS) $(LIBC) $?
	$(RL) $(RLFLAGS) $(LIBC)
