#include <errno.h>
#include <stdio.h>

#include <scc/mach.h>

#include "libmach.h"

#include "elf/fun.h"
#include "coff32/fun.h"

static int (*ops[NFORMATS])(int, long, char **, long *, FILE *);

static int
setidx(int type, long nsymbols, char *names[], long offs[], FILE *fp)
{
	return setidx32(BIG_ENDIAN, nsymbols, names, offs, fp);
}

int
setindex(int type, long nsyms, char **names, long *offs, FILE *fp)
{
	int fmt;

	fmt = FORMAT(type);
	if (fmt >= NFORMATS) {
		errno = ERANGE;
		return -1;
	}

	return (*ops[fmt])(type, nsyms, names, offs, fp);
}

static int (*ops[NFORMATS])(int, long, char **, long *, FILE *) = {
	[COFF32] = setidx,
	[ELF] = setidx,
};
