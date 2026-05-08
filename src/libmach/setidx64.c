#include <stdio.h>
#include <string.h>

#include <scc/mach.h>

#include "libmach.h"

int
setidx64(int order, long nsyms, char *names[], long offs[], FILE *fp)
{
	long i;
	size_t len;
	unsigned char buff[8];

	pack(order, buff, "q", (long long) nsyms);
	fwrite(buff, 8, 1, fp);

	for (i = 0; i < nsyms; i++) {
		pack(order, buff, "q", (long long) offs[i]);
		fwrite(buff, 8, 1, fp);
	}

	for (i = 0; i < nsyms; i++) {
		len = strlen(names[i]) + 1;
		fwrite(names[i], len, 1, fp);
	}

	return fflush(fp) == EOF ? -1 : 0;
}
