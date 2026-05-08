.POSIX:

PROJECTDIR =../../..
include $(PROJECTDIR)/scripts/rules.mk

OBJS =\
	elfarchs.o\
	elfdel.o\
	elfgetsec.o\
	elfgetsym.o\
	elfloadmap.o\
	elfnew.o\
	elfprobe.o\
	elfread.o\
	elftype.o\

ELFHDRS =\
	$(INCDIR)/bits/scc/elf/elfent.h\
	$(INCDIR)/bits/scc/elf/elfhdr.h\
	$(INCDIR)/bits/scc/elf/elfphdr.h\
	$(INCDIR)/bits/scc/elf/elfrel.h\
	$(INCDIR)/bits/scc/elf/elfshdr.h\
	$(INCDIR)/bits/scc/elf/elftypes.h\


all: $(OBJS)

$(OBJS): $(ELFHDR)

dep:
	@{ printf 'ELFOBJS=\\\n';\
	printf '\telf/%s\\\n' $(OBJS); } > deps.mk

distclean:
	rm -f deps.mk
