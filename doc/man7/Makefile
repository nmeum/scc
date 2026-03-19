.POSIX:

PROJECTDIR = ../..
include $(PROJECTDIR)/scripts/rules.mk

PAGES =\
	scc-ir.7\

.SUFFIXES: .man

NODEP = 1

all: $(PAGES)

.man.7:
	trap 'rm -f $tmp' EXIT;\
	trap 'exit 1' HUP INT TERM;\
	tmp=$$$$.tmp;\
	sed '/\.TH/ s/VERSION/$(VERSION)/' $< > $$tmp &&\
	mv $$tmp $@
	cp $@ $(MANDIR)/man7/

clean:
	rm -f *.7
