.POSIX:

DIRS  =\
	doc\
	src\
	src/libc\
	src/libcrt\
	include/scc/bits/scc\
	tests\

PROJECTDIR = .
include scripts/rules.mk

ROOT = $(DESTDIR)$(PREFIX)
NODEP = 1

all:
	+@$(MAKE) -f main.mk doc
	+@$(MAKE) -f main.mk toolchain
	+@$(MAKE) -f main.mk $(ARCH)

config: FORCE
	+@cd include/scc/bits/scc && $(MAKE)

install: all
	$(SCRIPTDIR)/install $(ROOT)
	+@$(MAKE) -f main.mk install-$(ARCH)

uninstall:
	$(SCRIPTDIR)/uninstall $(ROOT)
	+@$(MAKE) -f main.mk uninstall-$(ARCH)

toolchain: src
libc: src/libc
libcrt: src/libcrt

$(DIRS): dirs

dirs: $(SCRIPTDIR)/dirs
	xargs mkdir -p < $(SCRIPTDIR)/dirs
	touch dirs

clean: FORCE
	xargs rm -rf < $(SCRIPTDIR)/dirs
	find . -name '*.gcno' -o -name '*.gcda' | xargs rm -f
	rm -rf dirs coverage

distclean: clean
	rm config.mk
	rm -f include/scc/bits/scc/cstd.h
	rm -f include/scc/bits/scc/sys.h
	rm -f include/scc/bits/scc/config.h
	rm -rf scc-* .scc-*
	rm -f *.gz *.sig

dist:
	mkdir .scc-$(VERSION)
	cp -R * .scc-$(VERSION)/
	mv .scc-$(VERSION) scc-$(VERSION)
	find scc-$(VERSION) -name '.gitignore' | xargs rm
	tar -cf - scc-$(VERSION) | gzip > scc-$(VERSION).tar.gz
	rm -rf scc-$(VERSION)

include scripts/amd64.mk
include scripts/arm.mk
include scripts/arm64.mk
include scripts/i386.mk
include scripts/ppc.mk
