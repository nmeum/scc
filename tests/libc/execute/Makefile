.POSIX:

PROJECTDIR = ../../..
include $(PROJECTDIR)/scripts/rules.mk

PROJ_CFLAGS = $(CFLAGS)
PROJ_LDFLAGS = $(LDFLAGS)
CC=$(SCC)

all:
	@CC='$(CC)' \
	CFLAGS='$(PROJ_CFLAGS)' \
	LDFLAGS='$(PROJ_CFLAGS)' \
	./runtests.sh libc-tests.lst

tests:
	@$(MAKE) |\
	grep -v TODO |\
	grep FAIL >/dev/null &&\
	printf '[FAIL]' || printf '[PASS]'; printf '\tlibc/execute\n'

clean:
	rm -f *.o *core test.log `awk '{print $$1}' libc-tests.lst`
