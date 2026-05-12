#include <sys.h>

#include <stdio.h>
#include <string.h>

#include "../syscall.h"

#undef tmpnam

char *
tmpnam(char *s)
{
	static char tmpl[] = _TMPNAME;
	char *p, *beg;


	for (beg = tmpl; *beg < '0' || *beg > '9'; ++beg)
			;

	do {
		for (p = beg; *p == '9'; *p++ = '0')
			;
		if (*p == '\0')
			return NULL;
		++*p;
	} while (_access(tmpl, F_OK) == 0);

	if (s)
		strcpy(s, tmpl);
	return tmpl;
}
