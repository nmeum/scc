.POSIX:

PROJECTDIR = ../../..
include $(PROJECTDIR)/scripts/rules.mk

CC=$(SCC)
PROJ_CFLAGS = $(CFLAGS)

all:
	@CC='$(CC)' ./runtests.sh scc-tests.lst

tests:
	@$(MAKE) |\
	grep -v TODO |\
	grep FAIL >/dev/null &&\
	printf '[FAIL]' || printf '[PASS]'; printf '\tcc/execute\n'

clean:
	rm -f a.out *.s *.s *.as *.o *.ir *.qbe *core* test.log tests.h tmp_*.c
