#include <stdio.h>
#include <string.h>
#include <wchar.h>

#undef clearerr

void
clearerr(FILE *fp)
{
	fp->flags &= ~(_IOERR | _IOEOF);
	memset(&fp->mbs, 0, sizeof(mbstate_t));
}
