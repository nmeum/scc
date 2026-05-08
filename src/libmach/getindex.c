#include <errno.h>
#include <stdio.h>

#include <scc/mach.h>

#include "libmach.h"

#include "elf/fun.h"
#include "coff32/fun.h"

static int (*ops[NFORMATS])(int, long *, char ***, long **, FILE *);

static int
getidx(int type, long *nsyms, char ***namep, long **offsp, FILE *fp)
{
        return getidx32(BIG_ENDIAN, nsyms, namep, offsp, fp);
}

int
getindex(int type, long *nsyms, char ***names, long **offs, FILE *fp)
{
	int fmt;

	fmt = FORMAT(type);
	if (fmt >= NFORMATS) {
		errno = ERANGE;
		return -1;
	}

	return (*ops[fmt])(type, nsyms, names, offs, fp);
}

static int (*ops[NFORMATS])(int, long *, char ***, long **, FILE *) = {
	[COFF32] = getidx,
	[ELF] = getidx,
};

