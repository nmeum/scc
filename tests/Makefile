.POSIX:

DIRS =\
	ar/execute\
	nm/execute\
	as/execute\
	ld/execute\
	size/execute\
	strip/execute\
	libc/execute\
	cc/execute cc/error\
	make/execute make/error\

PROJECTDIR = ..
include $(PROJECTDIR)/scripts/rules.mk

all:
	@trap 'rm -f $$$$.tmp' EXIT ;\
	trap 'exit $?' INT HUP TERM;\
	for i in $(DIRS);\
	do \
		cd $$i;\
		$(MAKE) tests;\
		cd -;\
	done | \
	grep -e PASS -e FAIL -e SKIP |\
	tee $$$$.tmp &&\
	grep FAIL $$$$.tmp > /dev/null && exit 1 || exit 0

dep:
