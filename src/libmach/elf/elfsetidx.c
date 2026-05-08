#include <stdio.h>

#include <scc/mach.h>
#include <scc/coff32.h>

#include "../libmach.h"
#include "fun.h"

int
elfsetidx(int type, long nsymbols, char *names[], long offs[], FILE *fp)
{
	return setidx32(BIG_ENDIAN, nsymbols, names, offs, fp);
}
