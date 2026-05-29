.POSIX:

PROJECTDIR = ../../..
include $(PROJECTDIR)/scripts/rules.mk

CC=$(SCC)

all:
	@CC='$(CC)' ./runtests.sh scc-tests.lst

tests:
	@$(MAKE) |\
	grep -v TODO |\
	grep FAIL >/dev/null &&\
	printf '[FAIL]' || printf '[PASS]'; printf '\tcc/error\n'

clean:
	rm -f *.as *.o *.ir *.qbe *core test.log
