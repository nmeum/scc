CC = $(SCC) -t $(SYS) -a $(ARCH)
AR=$(SCC_AR)
RANLIB=$(SCC_RANLIB)

SYSERRNO = $(INCDIR)/bits/$(SYS)/sys/errno.h

LIBC = $(LIBCDIR)/libc.a
CRT = $(LIBCDIR)/crt.o

# Rules

.SUFFIXES: .$O

_sys_errlist.c: $(SYSERRNO)
	../../mkerrstr $(SYSERRNO)

_sys_errlist.$O: _sys_errlist.c
	$(CC) $(CFLAGS) -c -o $@ _sys_errlist.c

$(CRT): crt.$O
	cp crt.$O $@

clean: clean-libc

clean-libc: FORCE
	rm -f *.5? *.6? *.7? *.8? *.z *.q

.c.$O:
	$(CC) $(CFLAGS) -o $@ -c $<

.s.$O:
	$(AS) $(PROJ_ASFLAGS) $< -o $@
