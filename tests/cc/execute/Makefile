.POSIX:

PROJECTDIR = ../../..
include $(PROJECTDIR)/scripts/rules.mk

CC=$(SCC)

all:
	@CC='$(CC)' ./runtests.sh scc-tests.lst

.c:
	$(CC) -Isysinclude $(CFLAGS) $(LDFLAGS) -o $@ $< test.c

tests:
	@$(MAKE) |\
	grep -v TODO |\
	grep FAIL >/dev/null &&\
	printf '[FAIL]' || printf '[PASS]'; printf '\tcc/execute\n'

clean:
	rm -f a.out *.s *.s *.as *.o *.ir *.qbe *core* test.log tests.h tmp_*.c
	xargs rm -f < scc-tests.lst
