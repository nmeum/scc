.POSIX:

PROJECTDIR = ../../..
include $(PROJECTDIR)/scripts/rules.mk

CC=$(SCC)
PROJ_CFLAGS = $(CFLAGS)

all:
	CC=$(CC) ./runtests.sh libc-tests.lst

tests:
	@$(MAKE) |\
	grep -v TODO |\
	grep FAIL >/dev/null &&\
	printf '[FAIL]' || printf '[PASS]'; printf '\tlibc/execute\n'

clean:
	rm -f *.o *core test.log `awk '{print $$1}' libc-tests.lst`
