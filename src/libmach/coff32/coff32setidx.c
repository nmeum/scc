#include <stdio.h>

#include <scc/mach.h>
#include <scc/coff32.h>

#include "../libmach.h"
#include "fun.h"

int
coff32setidx(int type, long nsymbols, char *names[], long offs[], FILE *fp)
{
	return setidx32(ORDER(type), nsymbols, names, offs, fp);
}
