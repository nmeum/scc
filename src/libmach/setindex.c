#include <errno.h>
#include <stdio.h>

#include <scc/mach.h>

#include "libmach.h"

#include "elf/fun.h"
#include "coff32/fun.h"

static int (*ops[NFORMATS])(int, long, char **, long *, FILE *) = {
	[COFF32] = coff32setidx,
	[ELF] = elfsetidx,
};

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

