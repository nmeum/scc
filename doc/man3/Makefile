.POSIX:

PROJECTDIR = ../..
include $(PROJECTDIR)/scripts/rules.mk

PAGES =\
	asctime.3\
	clock.3\
	ctime.3\
	difftime.3\
	gmtime.3\
	locale.h.3\
	localeconv.3\
	localtime.3\
	longjmp.3\
	mbtowc.3\
	memchr.3\
	memcmp.3\
	memcpy.3\
	memmove.3\
	memset.3\
	mktime.3\
	setjmp.3\
	setjmp.h.3\
	setlocale.3\
	strcat.3\
	strchr.3\
	strcmp.3\
	strcoll.3\
	strcpy.3\
	strcspn.3\
	strerror.3\
	strftime.3\
	string.h.3\
	strlen.3\
	strncat.3\
	strncmp.3\
	strncpy.3\
	strpbrk.3\
	strrchr.3\
	strspn.3\
	strstr.3\
	strtok.3\
	strxfrm.3\
	time.3\
	time.h.3\
	wchar.h.3\

.SUFFIXES: .man

NODEP = 1

all: $(PAGES)

.man.3:
	trap 'rm -f $tmp' EXIT;\
	trap 'exit 1' HUP INT TERM;\
	tmp=$$$$.tmp;\
	sed '/\.TH/ s/VERSION/$(VERSION)/' $< > $$tmp &&\
	mv $$tmp $@
	cp $@ $(MANDIR)/man3/

clean:
	rm -f *.3
