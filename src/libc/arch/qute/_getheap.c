/*
 * TODO: This is a temporary solution until we implement brk()
 * in Qute. This has been copied from arch/darwin/_getheap.c.
 */

#include <errno.h>
#include <stddef.h>

#include "../../syscall.h"

static char heap[4096];

void *
_getheap(void)
{
	return heap;
}

int
_brk(void *addr)
{
	static char *cur = heap;
	char *p = addr;

	if (p < heap || p > &heap[sizeof(heap) - 1]) {
		errno = ENOMEM;
		return -1;
	}
	cur = p;

	return 0;
}
