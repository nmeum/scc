.POSIX:

PROJECTDIR = ../..
include $(PROJECTDIR)/scripts/rules.mk

PAGES =\
	scc.1\
	scc-addr2line.1\
	scc-ar.1\
	scc-cc.1\
	scc-cpp.1\
	scc-nm.1\
	scc-objdump.1\
	scc-ranlib.1\
	scc-size.1\
	scc-strip.1\

NODEP = 1
.SUFFIXES: .man

all: $(PAGES)

.man.1:
	trap 'rm -f $tmp' EXIT;\
	trap 'exit 1' HUP INT TERM;\
	tmp=$$$$.tmp;\
	sed '/\.TH/ s/VERSION/$(VERSION)/' $< > $$tmp &&\
	mv $$tmp $@
	cp $@ $(MANDIR)/man1/

clean:
	rm -f *.1
