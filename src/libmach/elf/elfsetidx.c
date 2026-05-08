#include <stdio.h>

#include <scc/mach.h>
#include <scc/coff32.h>

#include "../libmach.h"
#include "fun.h"

int
elfsetidx(int type, long nsymbols, char *names[], long offs[], FILE *fp)
{
	int (*f)(int, long, char *[], long[], FILE *);

	f = (BITS(type) == OBJ32) ? setidx32 : setidx64;

	return (*f)(ORDER(type), nsymbols, names, offs, fp);
}
